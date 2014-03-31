

const int _Bite = 3;
const int _Pat = 0; //interrupt #
// int.0 = 2; int.1 = 3;

const int _PatFreq = 1000;
const int _biteDuration = 200;
const int _startupDelay = 3000;

uint32_t bite_time;
bool wdtEnabled;

void setup() 
{
	//Set bite as HIGH
	digitalWrite(_Bite, HIGH);
	pinMode(_Bite, OUTPUT); 

	//set enabled to false, wait until first pat to enable
	wdtEnabled = false;

	//Make sure MEGA has time to start up
	delay(_startupDelay);

	//Just initalize the variable to something
	bite_time = millis();

	//Attach interrupt to call pat function on change
	attachInterrupt(_Pat, pat, CHANGE);
}

void loop() 
{
	if (wdtEnabled && millis() >= bite_time)
	{
		detachInterrupt(_Pat, pat);
		//Reset
		digitalWrite(_Bite, LOW);
		delay(_biteDuration);
		digitalWrite(_Bite, HIGH);
		wdtEnabled = false;
	}
}

void pat()
{
	wdtEnabled = true;
	bite_time = millis() + _PatFreq;
}