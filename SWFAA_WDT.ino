

const int _Bite = 3;
const int _Pat = 0; //interrupt #
// int.0 = 2; int.1 = 3;

const int _PatFreq = 1000;
const int _biteDuration = 200;
const int _startupDelay = 3000;
const int _patResetCount = 3;

uint32_t bite_time;
bool wdtEnabled;
int currentPats;

void setup() 
{
	//Set bite as HIGH
	digitalWrite(_Bite, HIGH);
	pinMode(_Bite, OUTPUT); 

	currentPats = 0;

	Serial.begin(115200);
  	while (!Serial); 

	//set enabled to false, wait until first pat to enable
	wdtEnabled = false;

	//Make sure MEGA has time to start up
	delay(_startupDelay);

	//Just initalize the variable to something
	bite_time = millis();

	//Attach interrupt to call pat function on change
	attachInterrupt(_Pat, pat, CHANGE);
	Serial.println("started");
}

void loop() 
{
	if (wdtEnabled && millis() >= bite_time)
	{
		Serial.println("reset");
		detachInterrupt(_Pat);
		//Reset
		digitalWrite(_Bite, LOW);
		delay(_biteDuration);
		digitalWrite(_Bite, HIGH);

		Serial.println("disabled");
		wdtEnabled = false;
		currentPats = 0;
		attachInterrupt(_Pat, pat, CHANGE);
	}
}

void pat()
{
	Serial.println("pat");
	if(!wdtEnabled)
	{
		if(_patResetCount <= currentPats)
		{
			Serial.println("enabled");
			wdtEnabled = true;
		}
		else
		{
			currentPats++;
		}
	}
	bite_time = millis() + _PatFreq;
}