#define heaterSelPin 5
 
void setup() {
    Serial.begin(9600);
    pinMode(heaterSelPin,OUTPUT);   // set the heaterSelPin as digital output.
    digitalWrite(heaterSelPin,LOW); // Start to heat the sensor
}
 float ethanolInCO(uint16_t co)
{
    float etanol;

    if (co == 0)
    {
        etanol = 0;
    }
    else if (co <= 10) 
    {
        etanol = co / 10.0;
    }
    else if (co > 10 && co <= 50)
    {
        etanol = (float)(6 / 50.0) * co;
    }
    else if (co > 50 && co <= 100)
    {
        etanol = (0.18 * co);
    }
    else if (co > 100)
    {
        etanol = (float)(274 / 500.0) * co;
    }
    return etanol;
}
float ppm2mgL(uint16_t ppm)
{
    float mgL;
    
    mgL = (1.82 * ppm) / 1000.0;
    return mgL;
}
void loop() {
    float sensor_volt;
    float RS_air; //  Get the value of RS via in a clear air
    float sensorValue = 0;
 
/*--- Get a average data by testing 100 times ---*/
    for(int x = 0 ; x < 10 ; x++)
    {
        sensorValue = sensorValue + analogRead(A5);
    }
    sensorValue = sensorValue/10.0;
/*-----------------------------------------------*/
    uint16_t CO_ppm = map(sensorValue,0,1024,1,1000);
    float ethanol_ppm = ethanolInCO(CO_ppm);
    float ethanol_mgl = ppm2mgL(ethanol_ppm);
//    sensor_volt = (sensorValue/1024)*5.0;
    //RS_air = sensor_volt/(5.0-sensor_volt); // omit *R16
    Serial.println(ethanol_mgl);
    delay(100);
}
