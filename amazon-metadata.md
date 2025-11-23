# Q3 – Item metadata for an Amazon shirt

Assumption: We are modelling a shirt being sold on an e‑commerce platform similar to Amazon. Below is the metadata I would store for a shirt and how it would be used.

## Core product fields

- Product ID (internal unique id)
- SKU (seller’s unique stock code)
- Title (e.g. "Men's Slim Fit Cotton Shirt")
- Brand (e.g. "Levi's")
- Category and sub‑category (Clothing → Men → Shirts → Casual)
- Detailed description

These fields are mainly used for search, SEO, and to uniquely identify and display the product on PDP / listing pages. 

## Variant‑level metadata (color/size)

A shirt usually has multiple variants. For each variant I would store:

- Color (Blue, Black, White…)
- Size (S, M, L, XL, XXL)
- Fit (Slim, Regular, Relaxed)
- Pattern (Solid, Striped, Checks, Printed)
- Sleeve type (Full, Half)
- Neck type (Collar, Mandarin, Henley)
- Individual SKU for the variant
- Images specific to that color
- Inventory quantity per warehouse
- Price, discount, currency

This is used to show correct availability per size/color, run size‑wise discounts, and avoid overselling a specific variant.  

## Material, quality & care

- Fabric (100% cotton, cotton blend, linen, etc.)
- GSM / fabric weight if relevant
- Care instructions (machine wash, hand wash, do not bleach)
- Country of origin
- Any certifications (organic cotton, fair‑trade etc.)

This metadata helps with filters (e.g. “only cotton”), builds customer trust, and is also required for compliance in some regions.  

## Pricing and commercial fields

- MRP / list price
- Selling price
- Discount percentage
- Tax class / GST slab
- Shipping cost or shipping profile
- Offers (bank offers, coupons, lightning deal flags)

Pricing data feeds into the recommendation/promotion engines and is also used by internal tools to run experiments on discounts and conversion.

## Logistics & dimensions

- Net weight of shirt
- Packed weight
- Package dimensions (L x W x H)
- HSN / product tax code

Logistics teams use this to decide packaging type, courier selection and to estimate shipping costs shown to the customer. 

## Seller and performance metadata

- Seller ID and seller name
- Fulfilment type (FBA / seller‑fulfilled)
- Average rating for the product
- Number of reviews
- Rating distribution (1–5 stars)
- Return rate for this SKU

These fields are used in ranking: for similar shirts, the system can push higher rated / lower return‑rate items up in search results. 

## How this metadata is used in the system

- **Search & filtering** – category, brand, material, color, size, and price are indexed so users can filter like "Men → Shirts → Cotton → Full sleeve → Under ₹1500".
- **Recommendations** – brand, category, price band and performance metrics feed collaborative filtering / “similar items” recommendation models.    
- **Inventory & pricing** – variant‑level stock and price allow dynamic pricing (higher discount for overstocked sizes) and out‑of‑stock handling.  
- **Analytics** – conversion rate, return rate, click‑through rate etc. per product help the business decide whether to improve content, change images or stop selling a particular shirt. 
