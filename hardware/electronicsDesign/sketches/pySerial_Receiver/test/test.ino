const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];        // temporary array for use when parsing

      // variables to hold the parsed data
char messageFromPC[numChars] = {0};
int xFromPC = 0;
int yFromPC = 0;
float floatFromPC = 0.0;

boolean newData = false;

//============

void setup() {
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
//    Serial.println("This demo expects 3 pieces of data - text, an integer and a floating point value");
//    Serial.println("Enter data in this style <HelloWorld, 12, 24.7>  ");
//    Serial.println();
}

//============

void loop() {
    recvWithStartEndMarkers();
    if (newData == true) {
        strcpy(tempChars, receivedChars);
            // this temporary copy is necessary to protect the original data
            //   because strtok() used in parseData() replaces the commas with \0
        parseData();
        showParsedData();
        newData = false;
    }
}

//============

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

//============

void parseData() {      // split the data into its parts

    char * strtokIndx; // this is used by strtok() as an index

    strtokIndx = strtok(tempChars,",");      // get the first part - the string
 //   strcpy(messageFromPC, strtokIndx); // copy it to messageFromPC
    xFromPC = atoi(strtokIndx);
 
    strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
    yFromPC = atoi(strtokIndx);     // convert this part to an integer

//    strtokIndx = strtok(NULL, ",");
  //  floatFromPC = atof(strtokIndx);     // convert this part to a float

}

//============

void showParsedData() {
//    Serial.print("Message ");
//    Serial.println(messageFromPC);
//    Serial.print("xInteger ");
//    Serial.println(xFromPC);
    if(yFromPC > 240 and xFromPC > 240)
    digitalWrite(LED_BUILTIN, HIGH);
    else if(yFromPC < 240 and xFromPC < 240)
    digitalWrite(LED_BUILTIN, LOW);
//    Serial.print("yInteger ");
//    Serial.println(yFromPC);
}
