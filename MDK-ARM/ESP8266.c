void esp8266_init()
{
	HAL_UART_Transmit(&huart2,buffer,len,1000);
  HAL_UART_Transmit("AT+RST\r\n",5000); // Reset ESP8266 module
  send_receive_ESP8266("AT+CWMODE=1\r\n",1000); // Configure ESP8266 as station mode
  send_receive_ESP8266("AT+CWQAP\r\n",1000); // Disconnect ESP8266 from all previously connected wifi devices
  send_receive_ESP8266("AT+CWJAP=\"stevenleeyongwah@unifi\",\"ss8828ss\"\r\n",7000); // Disconnect ESP8266 from all previously connected wifi devices
  send_receive_ESP8266("AT+CIFSR\r\n",3000); // Get IP address
  send_receive_ESP8266("AT+CIPMUX=1\r\n",1000); // Configure for multiple connections
  send_receive_ESP8266("AT+CIPSERVER=1,80\r\n",1000); // Turn on server on port 80
}
void send_receive_ESP8266(String command, const int timeout) // Transmit ESP8266 command from Arduino to ESP8266
{
  String response = "";
  esp8266.print(command); // Send the command to ESP8266 
  long int time1 = millis(); // Store the current time in time1
  while( (time1+timeout) > millis()) // Wait for timeout
  {
    while(esp8266.available()) // Check if esp8266 replies?
    {
      char c = esp8266.read(); // Read each character and stored in c
      response += c;           // Combine each of the read character into string
    }
  }
  Serial.print(response); // Print the string on Arduino serial monitor
}