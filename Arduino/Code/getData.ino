void getData(Data* data){
	Serial.println(F("Hello I am getting your DATA!!! :)"));
	int Navg =20 ;
	uint16_t datatemperature = 0;
	uint16_t datapH = 0;
	uint16_t dataDO = 0;
	int dataturbidity = 0;

	for(int i=0; i<Navg; i++){ //take 10 readings and then average them
	 datatemperature += analogRead(pinTemperature);
	 datapH += analogRead(pinPH);
	 dataDO += analogRead(pinDO);
	 dataturbidity += analogRead(pinTurbidity);
	}
	datatemperature = datatemperature/Navg;
	datapH = datapH/Navg;
	dataDO = dataDO/Navg;
	dataturbidity = dataturbidity/Navg;

	if( dataturbidity >= 703) {
		dataturbidity = 703; //limit the maximum to 703
		}

	// randomSeed(analogRead(5));
	// data->temperature = 30.34;
	// data->pH = 7.0;
	// data->DO = 5.01;
	// data->turbidity = 50;

	// data->temperature = random(0, 30);
	// data->pH = random(0, 14);	
	// data->DO = random(0, 100);
	// data->turbidity = random(0, 1000);

	//pH value
	//4-20mA,  0-14 pH, Accuracy: 2% of full scale, -5 to +55°C, http://www.globalw.com/products/wq201.html
	//using a 220ohm resistor, we get 0.88-4.4V full scale
	//subtract 0.88 to get 0-3.52V
	//divide by 3.52 and multiply with 14 to get pH value
	data->pH = (datapH*(5.0/1023.0)-0.88)/3.52*14.00;
	if (data->pH <0) data->pH = 0;

	//DO value
	//4-20mA, 0-8ppm, 0-100%, Accuracy: ±0.5% of full scale, 10 seconds warm up time, -40 to +55°C, http://www.globalw.com/products/wq401.html
	//using a 220ohm resistor, we get 0.88-4.4V full scale
	//subtract 0.88 to get 0-3.52V
	//divide by 3.52 and multiply with 100 to get DO value
	data->DO = (dataDO*(5.0/1023.0)-0.88)/3.52*100.00;
	if (data->DO <0) data->DO = 0;

	//Temperature value
	//4-20mA, -50 to +50°C, ±0.1°C, 5 seconds minimum, -50 to +100°C, http://www.globalw.com/products/wq101.html
	//using a 220ohm resistor, we get 0.88-4.4V full scale
	//subtract 0.88 to get 0-3.52V
	//subtract by 1.76 to get -1.76 - 1.76
	//divide by 1.76 and multiply with 50 to get Temperature value in degree Celsius
	data->temperature = ((datatemperature*(5.0/1023.0)-0.88)-1.76)/1.76*50;

	//Turbidity value
	//0-3.45V, 0-4000 NTU units
	//about 702, 703 ADC value
	//-5.69
	//turbidity = voltage * -4000/703 + 4000
	// Serial.print(F("dataturbidity is: "));
	// Serial.println( dataturbidity*-5.69);
	// Serial.println(((dataturbidity*(-4000))/703));
	data->turbidity = (dataturbidity*-5.69) + 4000;
	if (data->turbidity <0) data->turbidity = 0;
}

void printData(Data* data){
	Serial.print(F("Temperature is: "));
	Serial.println(data->temperature);
	Serial.print(F("pH is: "));
	Serial.println(data->pH);
	Serial.print(F("DO is: "));
	Serial.println(data->DO);
	Serial.print(F("Turbidity is: "));
	Serial.println(data->turbidity);
}