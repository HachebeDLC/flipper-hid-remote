const assert = require('assert');

// Mock the Web Bluetooth API
Object.defineProperty(global, 'navigator', {
    value: {
        bluetooth: {
            requestDevice: async () => ({})
        }
    },
    configurable: true,
    writable: true
});

async function runTests() {
    try {
        const app = require('../src/web/app.js');
        
        // Mock characteristic
        let lastSentData = null;
        app.__setMockCharacteristic({
            writeValueWithoutResponse: async (data) => { lastSentData = data; },
            writeValue: async (data) => { lastSentData = data; },
            properties: { writeWithoutResponse: true }
        });

        // 1. Test sendKeyDownToFlipper
        // HID Code 0x04 is 'a'
        await app.sendKeyDownToFlipper(0x04);
        assert.deepStrictEqual(lastSentData, new Uint8Array([0x03, 0x04]), 'sendKeyDownToFlipper failed');
        
        // 2. Test sendKeyUpToFlipper
        await app.sendKeyUpToFlipper(0x04);
        assert.deepStrictEqual(lastSentData, new Uint8Array([0x04, 0x04]), 'sendKeyUpToFlipper failed');
        
        // 3. Test sendModifiersToFlipper
        // Shift = 0x02
        await app.sendModifiersToFlipper(0x02);
        assert.deepStrictEqual(lastSentData, new Uint8Array([0x05, 0x02]), 'sendModifiersToFlipper failed');

        console.log('Web Keyboard logic tests passed.');
    } catch (e) {
        console.error('Test failed:', e.message);
        process.exit(1);
    }
}

runTests();
