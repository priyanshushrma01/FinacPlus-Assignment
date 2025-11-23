// Q1 – Special Cipher

function specialCipher(str, rotation) {
    // Step 1: Apply Caesar cipher
    let caesarResult = '';
    for (let char of str) {
        if (char >= 'A' && char <= 'Z') {
            caesarResult += String.fromCharCode(
                ((char.charCodeAt(0) - 65 + rotation) % 26) + 65
            );
        } else if (char >= 'a' && char <= 'z') {
            caesarResult += String.fromCharCode(
                ((char.charCodeAt(0) - 97 + rotation) % 26) + 97
            );
        } else {
            caesarResult += char;
        }
    }
    
    // Step 2: Apply Run-Length Encoding
    let rleResult = '';
    let count = 1;
    
    for (let i = 0; i < caesarResult.length; i++) {
        if (i + 1 < caesarResult.length && caesarResult[i] === caesarResult[i + 1]) {
            count++;
        } else {
            rleResult += caesarResult[i];
            if (count > 1) rleResult += count;
            count = 1;
        }
    }
    
    return rleResult;
}

// Test cases
console.log(specialCipher("AABCCC", 3));  
console.log(specialCipher("AAA", 1));    
console.log(specialCipher("HELLO", 13));
