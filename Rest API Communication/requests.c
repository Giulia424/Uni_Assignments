#include <stdlib.h> /* exit, atoi, malloc, free */
#include <stdio.h>
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helper.h"
#include "request.h"

#define BUFLEN 4096
#define LINELEN 1000

char *compute_get_request(char *host, char *url, char *content_type, char *query_params, char *authorization,
                          char **cookies)
{
    char *message = (char *)calloc(BUFLEN, sizeof(char));
    char *line = (char *)calloc(LINELEN, sizeof(char));
    if (query_params == NULL)

        sprintf(line, "GET %s HTTP/1.1", url);
    else
        sprintf(line, "GET %s?%s HTTP/1.1", url, query_params);
    compute_message(message, line);

    if (authorization != NULL)
    {
        sprintf(line, "Authorization: %s", authorization);
        compute_message(message, line);
    }

    sprintf(line, "Host: %s", host);
    compute_message(message, line);

    if (content_type != NULL)
    {
        sprintf(line, "Accept: %s", content_type);
        compute_message(message, line);
    }

    memset(line, 0, LINELEN);
    if (cookies != NULL)
    {
        sprintf(line, "Cookie: %s", cookies[0]);
        compute_message(message, line);
    }
    compute_message(message, "");

    free(line);

    return message;
}

char *compute_delete_request(char *host, char *url, char *content_type, char *query_params, char *authorization,
                             char **cookies)
{
    char *message = (char *)calloc(BUFLEN, sizeof(char));
    char *line = (char *)calloc(LINELEN, sizeof(char));

    if (query_params == NULL)

        sprintf(line, "DELETE %s HTTP/1.1", url);

    else
        sprintf(line, "DELETE %s?%s HTTP/1.1", url, query_params);
    compute_message(message, line);
    if (authorization != NULL)
    {
        sprintf(line, "Authorization: %s", authorization);
        compute_message(message, line);
    }

    sprintf(line, "Host: %s", host);
    compute_message(message, line);

    if (content_type != NULL)
    {
        sprintf(line, "Accept: %s", content_type);
        compute_message(message, line);
    }

    memset(line, 0, LINELEN);
    if (cookies != NULL)
    {
        sprintf(line, "Cookie: %s", cookies[0]);

        compute_message(message, line);
    }
    compute_message(message, "");

    free(line);

    return message;
}

char *compute_post_request(char *host, char *url, char *content_type, char **body_data,
                           int body_data_fields_count, char **cookies, int cookies_count,char *authorization)
{
    char *message = (char *)calloc(BUFLEN, sizeof(char));
    char *line = (char *)calloc(LINELEN, sizeof(char));
    char *body_data_buffer = (char *)calloc(LINELEN, sizeof(char));

    for (int i = 0; i < body_data_fields_count - 1; i++)
        compute_message(body_data_buffer, body_data[i]);

    strcat(body_data_buffer, body_data[body_data_fields_count - 1]);

    sprintf(line, "POST %s HTTP/1.1", url);
    compute_message(message, line);

    if (authorization != NULL)
    {
        sprintf(line, "Authorization: %s", authorization);
        compute_message(message, line);
    }

    sprintf(line, "Host: %s", host);
    compute_message(message, line);


    sprintf(line, "Content-Type: %s", content_type);
    compute_message(message, line);

    sprintf(line, "Content-Length: %ld", strlen(body_data_buffer));
    compute_message(message, line);

    if (cookies != NULL)
    {
        sprintf(line, "Cookie: %s", cookies[0]);
        for (int i = 1; i < cookies_count; i++)
        {
        char temp[LINELEN];
        strcpy(temp, line);
        sprintf(line, "%s; %s", temp, cookies[i]);
        }
        compute_message(message, line);
    }
    compute_message(message, "");
    compute_message(message, body_data_buffer);

    free(line);
    free(body_data_buffer);

    return message;
}
