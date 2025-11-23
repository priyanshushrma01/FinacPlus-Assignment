# Q4 – High Level Design: Portfolio Tracker

### Problem recap

We have around 250 users. Each user has at least one portfolio which can contain both stocks and mutual funds. Market prices come from an external API and are refreshed every 10 minutes. The system should store user portfolios and show an up‑to‑date view of total portfolio value and profit/loss.

---

## 1. High level design diagram

Below is a simple high‑level block diagram of the system:

            +----------------------+
            |   Web / Mobile UI    |
            +-----------+----------+
                        |
                        v
               +--------+--------+
               |    API Server   |
               | (Portfolio API) |
               +----+-------+----+
                    |       |
      portfolio API |       | scheduled job
                    |       v
            +-------+----------------+
            |   Price Fetcher Job   |
            | (runs every 10 mins)  |
            +-----------+-----------+
                        |
                        v
    +-------------------+--------------------+
    |                  Database              |
    |----------------------------------------|
    |  users           portfolios           |
    |  holdings        prices_latest        |
    |                                        |
    +-------------------+--------------------+
                        ^
                        |
                 optional cache
                        |
                    +---+---+
                    | Redis |
                    +-------+


---

## 2. Main components

**Client (Web / Mobile UI)**  
- Frontend that lets the user log in, see their portfolios, and view total value and P&L.  
- Calls REST APIs on the backend, for example `/portfolios/:id/summary`.

**API Server (Portfolio API)**  
- Exposes endpoints to manage users, portfolios and holdings.  
- For a given portfolio, reads holdings and latest prices, calculates current value and profit/loss, and returns a summary to the client.

**Database (Relational DB)**  
- Stores all persistent data: users, portfolios, holdings and latest market prices.  
- A relational database like PostgreSQL or MySQL is enough for 250 users.

**Price Fetcher Job (every 10 minutes)**  
- Background job or small service triggered by a scheduler/cron every 10 minutes.  
- Calls external market price APIs for all symbols that appear in user holdings and updates the latest price table.

**Redis Cache (optional, but useful)**  
- Stores pre‑computed portfolio summaries for quick reads.  
- Helps reduce load on the DB when the same user refreshes their portfolio multiple times within a 10‑minute window.

---

## 3. Data model

A simple schema that supports the use case:

- **users**  
  - `id` – primary key  
  - `name`  
  - `email`  
  - `created_at`

- **portfolios**  
  - `id` – primary key  
  - `user_id` – foreign key to `users.id`  
  - `name` – e.g. "Long term", "Retirement"

- **holdings**  
  - `id` – primary key  
  - `portfolio_id` – foreign key to `portfolios.id`  
  - `asset_type` – `STOCK` or `MUTUAL_FUND`  
  - `symbol` – e.g. `INFY`, `HDFCMF`  
  - `quantity`  
  - `avg_buy_price`

- **prices_latest**  
  - `id` – primary key  
  - `symbol`  
  - `asset_type`  
  - `last_price`  
  - `last_updated_at`

- **price_history** (optional, for charts / analysis)  
  - `id`  
  - `symbol`  
  - `asset_type`  
  - `price`  
  - `timestamp`

This is enough to compute total current value and P&L per portfolio.

---

## 4. Key flows

### 4.1 Price update flow (every 10 minutes)

1. Scheduler triggers the **Price Fetcher Job** every 10 minutes.  
2. The job queries the DB to get all distinct symbols from the `holdings` table.  
3. For each symbol, it calls the external market API to fetch the latest price.  
4. It updates the `prices_latest` table with the new `last_price` and `last_updated_at`.  
5. Optionally, it also inserts a row into `price_history` for historical charts.

### 4.2 User portfolio view flow

1. The user opens the portfolio page → the UI calls `GET /portfolios/:id/summary`.  
2. The API Server first checks Redis to see if there is a cached summary for this portfolio and it is still fresh.  
3. If cache hit and not expired, it returns the cached summary directly.  
4. If cache miss or stale:
   - Load all holdings for that portfolio from the `holdings` table.  
   - For each symbol, read the latest price from `prices_latest`.  
   - Calculate for each holding and for the total portfolio:
     - current value = `quantity × last_price`  
     - invested amount = `quantity × avg_buy_price`  
     - profit/loss and profit/loss %  
   - Store the computed summary in Redis with a TTL slightly less than 10 minutes.  
   - Return the summary to the client.

---

## 5. Notes and trade‑offs

- For the given scale (250 users), a single API server instance and one relational database are completely sufficient.  
- If the external price API fails temporarily, the system can still serve the last known prices from `prices_latest` and show “Last updated at …” to the user.  
- This design is simple to implement but can still be evolved later into multiple services (separate pricing service, separate portfolio service) if the system grows.  
