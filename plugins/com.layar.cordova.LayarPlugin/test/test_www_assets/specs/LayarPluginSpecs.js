/****************************************
 *
 * LayarPluginSpecs.js
 *
 * Created By Sumeru Chatterjee on 5/12/2014.
 *
 * Version: 0.1
 ****************************************
 * See the README.md for instructions on how to use this file
 ****************************************/

describe('LayarPlugin', function() {

    it('is defined', function() {
        expect(layarPlugin).toBeDefined();
    });

    it('is an instance of LayarPlugin', function() {
        expect(layarPlugin instanceof LayarPlugin).toBe(true);
    });
});