#include <stdio.h>      /* printf, sprintf */
#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include <ctype.h>
#include "helper.h"
#include "request.h"
#include "parson.h"
// CLOSE CONNECTION
struct client
{
    char **cookies;
    char *token;
};

void register_user()
{
    int sockfd, isValid = 0;
    char *message;
    char *response;
    char username[LINELEN], password[LINELEN];
    char *serialized_string = NULL;
    // CHECK CONNECTION
    sockfd = open_connection("34.254.242.81", 8080, AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    // I made sure we the password and username don't contail any blank spaces
    while (!isValid)
    {
        isValid = 1;
        printf("username=");
        fgets(username, LINELEN, stdin);
        username[strlen(username) - 1] = '\0';
        for (size_t i = 0; i < strlen(username); i++)
            if (isspace(username[i]))
            {
                isValid = 0;
                fprintf(stdout, "%s\n", "Username is invalid");
                break;
            }
    }

    isValid = 0;
    while (!isValid)
    {
        isValid = 1;
        printf("password=");
        fgets(password, LINELEN, stdin);
        password[strlen(password) - 1] = '\0';
        for (size_t i = 0; i < strlen(password); i++)
            if (isspace(password[i]))
            {
                isValid = 0;
                fprintf(stdout, "%s\n", "Password is invalid");
                break;
            }
    }

    // MAKE JSON OBJECT TO SEND TO SERVER
    JSON_Value *root_value = json_value_init_object();
    JSON_Object *root_object = json_value_get_object(root_value);
    json_object_set_string(root_object, "username", username);
    json_object_set_string(root_object, "password", password);
    serialized_string = json_serialize_to_string_pretty(root_value);

    char **body_data = (char **)malloc(sizeof(char *) * 100);
    for (int i = 0; i < 100; i++)
        body_data[i] = (char *)malloc(LINELEN);

    strcpy(body_data[0], serialized_string);
    message = compute_post_request("34.254.242.81", "/api/v1/tema/auth/register", "application/json", body_data, 1, NULL, 0, NULL);
    send_to_server(sockfd, message);

    response = receive_from_server(sockfd);

    // I made sure the response didn't contain any error(eg. Username was taken)    
    const char *content, *error;
    content = basic_extract_json_response(response);
    JSON_Value *root_val = json_parse_string(content);
    
    error = json_object_get_string(json_value_get_object(root_val), "error");
    if(error)
        printf("%s\n", error);
    else
        fprintf(stdout, "%s\n", "Register successful");

    free(message);
    free(response);

    for (int i = 0; i < 100; i++)
        free(body_data[i]);
    free(body_data);
    close_connection(sockfd);
}

void login_user(struct client *c)
{
    int sockfd, isValid = 0;
    char *message;
    char *response;
    char username[LINELEN], password[LINELEN];
    char *serialized_string = NULL;

    // CHECK CONNECTION
    sockfd = open_connection("34.254.242.81", 8080, AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    // Made sure once again the input for username and password are both valid
    while (!isValid)
    {
        isValid = 1;
        printf("username=");
        fgets(username, LINELEN, stdin);
        username[strlen(username) - 1] = '\0';
        for (size_t i = 0; i < strlen(username); i++)
            if (isspace(username[i]))
            {
                isValid = 0;
                fprintf(stdout, "%s\n", "Username is invalid");
                break;
            }
    }

    isValid = 0;
    while (!isValid)
    {
        isValid = 1;
        printf("password=");
        fgets(password, LINELEN, stdin);
        password[strlen(password) - 1] = '\0';
        for (size_t i = 0; i < strlen(password); i++)
            if (isspace(password[i]))
            {
                isValid = 0;
                fprintf(stdout, "%s\n", "Password is invalid");
                break;
            }
    }

    // MAKE JSON OBJECT TO SEND TO SERVER
    JSON_Value *root_value = json_value_init_object();
    JSON_Object *root_object = json_value_get_object(root_value);
    json_object_set_string(root_object, "username", username);
    json_object_set_string(root_object, "password", password);
    serialized_string = json_serialize_to_string_pretty(root_value);

    char **body_data = (char **)malloc(sizeof(char *) * 100);
    for (int i = 0; i < 100; i++)
        body_data[i] = (char *)malloc(LINELEN);

    strcpy(body_data[0], serialized_string);
    message = compute_post_request("34.254.242.81", "/api/v1/tema/auth/login", "application/json", body_data, 1, NULL, 0, NULL);
    send_to_server(sockfd, message);
    response = receive_from_server(sockfd);

    // Checked for errors
    const char *content, *error;
    content = basic_extract_json_response(response);
    JSON_Value *root_val = json_parse_string(content);
    
    error = json_object_get_string(json_value_get_object(root_val), "error");
    if(error)
        printf("%s\n", error);
    else
        fprintf(stdout, "%s\n", "Login successful");

    // I extracted the cookie to use in order to gain access to the library
    int i = 0;
    char *temp = (char *)calloc(2048, sizeof(char));
    char *cookie = (char *)calloc(2048, sizeof(char));
    temp = strstr(response, "connect.sid=");
    if (temp)
        while (temp[i] != ';')
        {
            cookie[i] = temp[i];
            i++;
        }

    c->cookies[0] = cookie;

    free(message);
    free(response);
    for (int i = 0; i < 100; i++)
        free(body_data[i]);
    free(body_data);
    close_connection(sockfd);
}
void enter_libr(struct client *c)
{
    int sockfd;
    char *message;
    char *response;
    // CHECK CONNECTION
    sockfd = open_connection("34.254.242.81", 8080, AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    message = compute_get_request("34.254.242.81", "/api/v1/tema/library/access", NULL, NULL, NULL, c->cookies);
    send_to_server(sockfd, message);
    response = receive_from_server(sockfd);

    // I extracted the token to use for authorization, to be added to the header  (for other actions later on, eg. delete, add)
    const char *content, *error, *token, *prefix = "Bearer ";
    content = basic_extract_json_response(response);

    JSON_Value *root_value = json_parse_string(content);
    token = json_object_get_string(json_value_get_object(root_value), "token");
    if (token != NULL)
    {
        printf("%s\n", "Access granted");
        strcpy(c->token, prefix);
        strcat(c->token, token);
    }
    else
    {
        error = json_object_get_string(json_value_get_object(root_value), "error");
        if (error)
            printf("%s\n", error);
    }

    json_value_free(root_value);
    free(message);
    free(response);

    close_connection(sockfd);
}
void all_books(struct client *c)
{
    int sockfd;

    char *message;
    char *response;
    // CHECK CONNECTION
    sockfd = open_connection("34.254.242.81", 8080, AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    message = compute_get_request("34.254.242.81", "/api/v1/tema/library/books", "application/json", c->cookies[0], c->token, NULL);
    send_to_server(sockfd, message);
    response = receive_from_server(sockfd);
    const char *content, *error,*title;
    double book_id;
    content = extract_json_array(response);
    JSON_Value *root_value = json_parse_string(content);
    JSON_Array *books =json_value_get_array(root_value);;
    JSON_Object *book;
    for(size_t i =0;i<json_array_get_count(books);i++)
    {
        book = json_array_get_object(books,i);
        book_id = json_object_get_number(book, "id");
        printf("id:%d\n", (int)book_id);
        title = json_object_get_string(book, "title");
        printf("title:%s\n\n", title);
        
    }
    error = json_object_get_string(json_value_get_object(root_value), "error");
    if (error)
        printf("%s\n", error);
    free(message);
    free(response);

    close_connection(sockfd);
}
void book(struct client *c)
{
    int sockfd;
    char *message;
    char *response;
    char id[LINELEN] = "";
    char path[LINELEN] = "";
    printf("id=");
    fgets(id, LINELEN, stdin);
    id[strlen(id) - 1] = '\0';

    strcat(path, "/api/v1/tema/library/books/");
    strcat(path, id);

    // CHECK CONNECTION
    sockfd = open_connection("34.254.242.81", 8080, AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    message = compute_get_request("34.254.242.81", path, NULL, NULL, c->token, c->cookies);
    send_to_server(sockfd, message);
    response = receive_from_server(sockfd);

    // GET BOOKS INFO
    const char *content, *error, *title, *author, *genre, *publisher;
    double book_id, page_count;
    content = basic_extract_json_response(response);

    JSON_Value *root_value = json_parse_string(content);
    book_id = json_object_get_number(json_value_get_object(root_value), "id");
    printf("id:%d\n", (int)book_id);
    title = json_object_get_string(json_value_get_object(root_value), "title");
    printf("title:%s\n", title);
    author = json_object_get_string(json_value_get_object(root_value), "author");
    printf("author:%s\n", author);
    publisher = json_object_get_string(json_value_get_object(root_value), "publisher");
    printf("publisher:%s\n", publisher);
    genre = json_object_get_string(json_value_get_object(root_value), "genre");
    printf("genre:%s\n", genre);
    page_count = json_object_get_number(json_value_get_object(root_value), "page_count");
    printf("page_count:%d\n", (int)page_count);
    error = json_object_get_string(json_value_get_object(root_value), "error");
    if (error)
        printf("%s\n", error);

    free(message);
    free(response);
    close_connection(sockfd);
}
void add(struct client *c)
{
    int sockfd, isValid = 0;
    char *message;
    char *response;
    char title[LINELEN], author[LINELEN], genre[LINELEN], publisher[LINELEN];
    char count[LINELEN];
    char *serialized_string = NULL;
    // CHECK CONNECTION
    sockfd = open_connection("34.254.242.81", 8080, AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    // GET INFO ABOUT BOOK TO BE ADDED
    printf("title=");
    fgets(title, LINELEN, stdin);
    title[strlen(title) - 1] = '\0';
    printf("author=");
    fgets(author, LINELEN, stdin);
    author[strlen(author) - 1] = '\0';
    printf("genre=");
    genre[strlen(genre) - 1] = '\0';
    fgets(genre, LINELEN, stdin);
    genre[strlen(genre) - 1] = '\0';
    printf("publisher=");
    fgets(publisher, LINELEN, stdin);
    publisher[strlen(publisher) - 1] = '\0';

    while (!isValid)
    {
        isValid = 1;
        printf("page_count=");
        fgets(count, LINELEN, stdin);
        count[strlen(count) - 1] = '\0';
        for (size_t i = 0; i < strlen(count); i++)
            if (!isdigit(count[i]))
            {
                isValid = 0;
                fprintf(stdout, "%s\n", "Page_count is invalid");
                break;
            }
    }

    // MAKE JSON OBJECT TO ADD BOOK
    JSON_Value *root_value = json_value_init_object();
    JSON_Object *root_object = json_value_get_object(root_value);
    json_object_set_string(root_object, "title", title);
    json_object_set_string(root_object, "author", author);
    json_object_set_string(root_object, "genre", genre);
    json_object_set_string(root_object, "publisher", publisher);
    json_object_set_string(root_object, "page_count", count);
    serialized_string = json_serialize_to_string_pretty(root_value);

    char **body_data = (char **)malloc(sizeof(char *) * 100);
    for (int i = 0; i < 100; i++)
        body_data[i] = (char *)malloc(LINELEN);

    strcpy(body_data[0], serialized_string);
    message = compute_post_request("34.254.242.81", "/api/v1/tema/library/books", "application/json", body_data, 1, c->cookies, 1, c->token);
    send_to_server(sockfd, message);
    response = receive_from_server(sockfd);

    const char *content, *error;
    content = basic_extract_json_response(response);
    JSON_Value *root_val = json_parse_string(content);
    error = json_object_get_string(json_value_get_object(root_val), "error");
    if(error)
        printf("%s\n", error);

    free(message);
    free(response);
    close_connection(sockfd);

}
void delete(struct client *c)
{
    int sockfd;
    char *message;
    char *response;
    char id[LINELEN] = "";
    char path[LINELEN] = "";
    printf("id=");
    fgets(id, LINELEN, stdin);
    id[strlen(id) - 1] = '\0';
    strcat(path, "/api/v1/tema/library/books/");
    strcat(path, id);

    sockfd = open_connection("34.254.242.81", 8080, AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    message = compute_delete_request("34.254.242.81", path, NULL, NULL, c->token, c->cookies);
    send_to_server(sockfd, message);
    response = receive_from_server(sockfd);
    
    const char *content, *error;
    content = basic_extract_json_response(response);
    JSON_Value *root_value = json_parse_string(content);
    
    error = json_object_get_string(json_value_get_object(root_value), "error");
    if(error)
        printf("%s\n", error);
    else
        fprintf(stdout, "%s\n", "Book deleted successful");

    free(message);
    free(response);
    close_connection(sockfd);
}

void logout()
{
    int sockfd;
    char *message;
    char *response;
    // CHECK CONNECTION
    sockfd = open_connection("34.254.242.81", 8080, AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    message = compute_get_request("34.254.242.81", "/api/v1/tema/auth/logout", NULL, NULL, NULL, NULL);
    send_to_server(sockfd, message);
    response = receive_from_server(sockfd);

    const char *content, *error;
    content = basic_extract_json_response(response);
    JSON_Value *root_value = json_parse_string(content);
    
    error = json_object_get_string(json_value_get_object(root_value), "error");
    if(error)
        printf("%s\n", error);
    else
        fprintf(stdout, "%s\n", "Logout successful");

    free(message);
    free(response);
    close_connection(sockfd);
}

int main()
{
    struct client c;
    char command[20];
    c.cookies = (char **)calloc(2048, sizeof(char *));
    c.token = (char *)calloc(2048, sizeof(char));
    while (1)
    {
        fgets(command, 20, stdin);
        command[strlen(command) - 1] = '\0';
        if ((strcmp(command, "register")) == 0)
            register_user();
        else if ((strcmp(command, "login")) == 0)
            login_user(&c);
        else if ((strcmp(command, "enter_library")) == 0)
        {
            if (c.cookies[0] == NULL)
                fprintf(stdout, "%s\n", "Authentification required");
            else
                enter_libr(&c);
        }
        else if ((strcmp(command, "get_books")) == 0)
        {
            if (c.token[0] == 0)
                fprintf(stdout, "%s\n", "Access is required");
            else
                all_books(&c);
        }
        else if ((strcmp(command, "get_book")) == 0)
        {
            if (c.token[0] == 0)
                fprintf(stdout, "%s\n", "Access is required");
            else
                book(&c);
        }
        else if ((strcmp(command, "add_book")) == 0)
        {
            if (c.token[0] == 0)
                fprintf(stdout, "%s\n", "Access is required");
            else 
            {
                add(&c);
            }
        }
        else if ((strcmp(command, "delete_book")) == 0)
        {
            if (c.token[0] == 0)
                fprintf(stdout, "%s\n", "Access is required");
            else
                delete (&c);
        }

        else if ((strcmp(command, "logout")) == 0)
        {
            if (c.cookies[0] == NULL)
                fprintf(stdout, "%s\n", "Authentification required");
            else
            {
                logout();
                memset(c.cookies, 0, 2048);
                memset(c.token, 0, 2048);
            }
        }
        else if ((strcmp(command, "exit")) == 0)
            break;
    }

    free(c.cookies);
    free(c.token);

    return 0;
}
