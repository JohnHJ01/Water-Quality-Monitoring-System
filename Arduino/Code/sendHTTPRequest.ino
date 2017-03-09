void constructHTTPRequest(char* msg){  
  msg[0] = 0; //reset the string  
  strcat(msg, "GET /log.php?");  
  strcat(msg, "te=");
  strcat(msg, temperature);
  strcat(msg, "&");
  strcat(msg, "do=");
  strcat(msg, DO);
  strcat(msg, "&");
  strcat(msg, "pH=");
  strcat(msg, pH);
  strcat(msg, "&");
  strcat(msg, "tu=");
  strcat(msg, turbidity);
  strcat(msg, "&");
  strcat(msg, "la=");
  strcat(msg, lat);
  strcat(msg, "&");
  strcat(msg, "ln=");
  strcat(msg, lng);  
  strcat(msg, " HTTP/1.1\r\nHost: ");
  strcat(msg, server);
  strcat(msg, "\r\nConnection: close\r\n\r\n");
}


void sendHTTPRequest(char* msg){
  // strcat(msg, "t=2016-11-18,23:01:00");
  // strcat(msg, "&");
  // strcat(msg, "te=30.0");
  // strcat(msg, "&");
  // strcat(msg, "do=7.05");
  // strcat(msg, "&");
  // strcat(msg, "pH=5.66");
  // strcat(msg, "&");
  // strcat(msg, "tu=7");
  // strcat(msg, "&");
  // strcat(msg, "la=5.1492");
  // strcat(msg, "&");
  // strcat(msg, "ln=100.492");
  // strcat(msg, " HTTP/1.1\r\nHost: ");
  // strcat(msg, server);
  // strcat(msg, "\r\nConnection: close\r\n\r\n");
  a7Client.write(msg);
}