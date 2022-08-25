#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <curl/curl.h>

#define USERAGENT "curl/7.84.0"

void request(char *url) {

  CURL *curl = curl_easy_init(); //initialize curl
  CURLcode res; //curl response

  //Curl options
  curl_easy_setopt(curl, CURLOPT_URL, url); //Curl website
  curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); //Curl redirect
  curl_easy_setopt(curl, CURLOPT_USERAGENT, USERAGENT); //Curl useragent

  res = curl_easy_perform(curl); //perform curl

  //Check for error
  if(res != CURLE_OK) {
    fprintf(stderr, "[-] Could not fetch Webpage\n[-] Error: %s\n", curl_easy_strerror(res));
    exit(-1);
  }
  
  //Clean up
  curl_easy_cleanup(curl);
}

void print_help() {
  printf("wttr - Show the weather in the terimnal\n");
  printf("\n");
  printf("Usage: wttr city [options]\n");
  printf("\n");
  printf("Options:\n");
  printf("  -v  print full weather for today and the next two days\n"); //three day forecast
  printf("  -q  print weather as one liner for today\n");               //one liner
  printf("  -f  print full weather in detail for today\n");             //detailed for today
  printf("  -d  print weather for today\n");                           //default only today
  printf("  -h  print this help message\n");                             //help 
}

int main(int argc, char *argv[]) {

  char url[1024] = "wttr.in/";

  int opt;
  
  strcat(url, argv[1]);
  
  while ((opt = getopt(argc, argv, "vqfdh")) != -1) {
    switch(opt) {
      case 'v':
        strcat(url, "");
        request(url);
        break;
      case 'q':
        strcat(url, "?format=4");
        request(url);
        break;
      case 'f':
        strcat(url, "?1");
        request(url);
        break;
      case 'd':
        strcat(url, "?0");
        request(url);
        break;
      case 'h':
        print_help();
        break;
      default:
        print_help();
        exit(EXIT_FAILURE);
    }
  }
  
  return 0;
}
