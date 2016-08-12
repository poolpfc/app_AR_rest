/****************************************
 *
 * LayarPluginDelegateSpecs.js
 *
 * Created By Sumeru Chatterjee on 5/12/2014.
 *
 * Version: 0.1
 ****************************************
 * See the README.md for instructions on how to use this file
 ****************************************/

describe('LayarPluginDelegate', function() {

    it('is defined.', function() {
        expect(delegate).toBeDefined();
    });

    it('has a constructor to create instances.', function() {
        var delegate = new LayarPluginDelegateDelegate();
        expect(delegate).toBeDefined();
        expect(delegate instanceof LayarPluginDelegate).toBe(true);
    });
});


