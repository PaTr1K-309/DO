#include <fcgi_stdio.h>
#include <stdlib.h>

int main() {
    while(FCGI_Accept() >= 0) {
        printf("Status: 200 OK \r\n");
        printf("Content-type: text/html\r\n\r\n");
        printf("<!doctype><html><body>Hello world!<body></html>\n");
    }
    return 0;
}