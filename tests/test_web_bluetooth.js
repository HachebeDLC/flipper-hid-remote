const assert = require('assert');

// Force override the built-in navigator object in Node.js
Object.defineProperty(global, 'navigator', {
    value: {
        bluetooth: {
            requestDevice: async () => {
                return {
                    name: 'Flipper Zero',
                    gatt: {
                        connect: async () => ({
                            getPrimaryService: async () => ({
                                getCharacteristic: async () => ({})
                            })
                        })
                    }
                };
            }
        }
    },
    configurable: true,
    writable: true
});

async function runTests() {
    try {
        const app = require('../src/web/app.js');
        const result = await app.connectToFlipper();
        assert.strictEqual(result, true, 'connectToFlipper should return true on success');
        console.log('Web Bluetooth tests passed.');
    } catch (e) {
        console.error('Test failed:', e.message);
        process.exit(1);
    }
}

runTests();
