// Originally found at 
// http://jheyman.github.io/blog/pages/ZwaveHomeAutomation/#z-way-server-automation-engine

LimitlessLED.prototype.init = function (config) {
    LimitlessLED.super_.prototype.init.call(this, config);

    var self = this;

	// Register a callback function on modifications of the "currentScene" value of 
        // command class 43 (SCENE_ACTIVATION) of the wall controller switch
	zway.devices[1].instances[0].commandClasses[43].data.currentScene.bind(function() {
		var value = zway.devices[1].instances[0].commandClasses[43].data.currentScene.value;
		console.log("LimitlessLED: SCENE detected = ", value);

		if (self.timer) {
		    // Timer is set, so we destroy it
		    clearTimeout(self.timer);
		}
		
		// Scene = 2 correponds to button DOWN pushed
		if (value === 2) {
			
			// Turn on the RGB LED (to full blue color) to show ongoing
			// transition to ECO mode
			//blue
			zway.devices[24].instances[2].SwitchMultilevel.Set(99);			
			//red
			zway.devices[24].instances[3].SwitchMultilevel.Set(0);
			// green	
			zway.devices[24].instances[4].SwitchMultilevel.Set(0);
			

			// Turn off FIBARO plug #1
			zway.devices[5].instances[0].SwitchBinary.Set(0);

			//
			// etc... for all other devices to be turned off
			//

			console.log("LimitlessLED is now ON ");

			// Turn LED back off to show completion (after 2 second delay)
			    self.timer = setTimeout(function () {
				// RGB notification
				zway.devices[24].instances[2].SwitchMultilevel.Set(0);
				self.timer = null;
			    }, 2*1000);


			// Scene = 1 correponds to button UP pushed
	        } else if (value === 1) {
			
			// Turn on the RGB LED (full green) to show ongoing 
			//transition out of ECO mode
			// green
			zway.devices[24].instances[4].SwitchMultilevel.Set(99);			
			// red			
			zway.devices[24].instances[3].SwitchMultilevel.Set(0);
			// blue
			zway.devices[24].instances[2].SwitchMultilevel.Set(0);

			// Turn FIBARO plug #1 back on
			//zway.devices[5].instances[0].SwitchBinary.Set(255);

			//
			// etc... for all other devices to be turned off
			//

			console.log("LimitlessLED is now OFF");

			// Turn LED back off to show completion (after 2 second delay)
			    self.timer = setTimeout(function () {
				zway.devices[24].instances[4].SwitchMultilevel.Set(0);
				self.timer = null;
			    }, 2*1000);

	        } else {
			console.log("LimitlessLED: unknown scene (", value, "): IGNORING");		
		}
	 });
};

