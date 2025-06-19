#include <winsock2.h>
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <unordered_map>
#include <libpq-fe.h>

#include <ctime>
#include <chrono>
#include <format>


std::vector<SOCKET> clients;
std::mutex clientsMutex;
std::unordered_map<std::string, SOCKET> userToSocketDictionary;

void storeMessage(std::string user, std::string receiver, std::string message, PGconn * conn) {
    std::string statement = "storeMessage";
    // loads parameter values into paramterValues to be input into statement
    const char *parameterValues[4];
    parameterValues[0] = user.c_str();
    parameterValues[1] = receiver.c_str();
    parameterValues[2] = message.c_str();

    // formatting for current time
    auto timeNow = std::chrono::system_clock::now();
    std::cout << timeNow << "\n";
    std::string timestampString = std::format("{:%Y-%m-%d %H:%M:%S%z}", timeNow);
    std::cout << "Formatted timestamp: " << timestampString << "\n";

    parameterValues[3] = timestampString.c_str();

    // formatting of statements
    // paramLengths: An array of lengths for binary parameters. For text parameters, set to 0 or NULL.
    int paramLengths[4] = {0, 0 , 0, 0}; // 0 indicates null-terminated string
    // paramFormats: An array indicating format (0 for text, 1 for binary). We're using text.
    int paramFormats[4] = {0, 0 , 0, 0};

    PGresult *result = PQexecPrepared(conn, statement.c_str(), 4, parameterValues, paramLengths, paramFormats, 0);

    // logging
    if (PQresultStatus(result) != PGRES_COMMAND_OK) {
        std::cerr << "Execution of prepared statement failed: " << PQerrorMessage(conn) << std::endl;
        PQclear(result);
        PQfinish(conn);
    } else {
        std::cout << "Success in adding message into offline databse || LINE 51\n";
        // Clear the execution result.
        PQclear(result);
    }
}

void insertOfflineMessage(std::string user, std::string receiver, std::string message, PGconn *conn) {
    std::string statement = "insertOfflineMessage";
    // loads the parameter values into paramterValues to be input into statement
    const char *parameterValues[3];
    parameterValues[0] = user.c_str();
    parameterValues[1] = receiver.c_str();
    parameterValues[2] = message.c_str();

    // formatting of statements
    // paramLengths: An array of lengths for binary parameters. For text parameters, set to 0 or NULL.
    int paramLengths[3] = {0, 0 , 0}; // 0 indicates null-terminated string
    // paramFormats: An array indicating format (0 for text, 1 for binary). We're using text.
    int paramFormats[3] = {0, 0 , 0};

    PGresult *result = PQexecPrepared(conn, statement.c_str(), 3, parameterValues, paramLengths, paramFormats, 0);

    // logging
    if (PQresultStatus(result) != PGRES_COMMAND_OK) {
        std::cerr << "Execution of prepared statement failed: " << PQerrorMessage(conn) << std::endl;
        PQclear(result);
        PQfinish(conn);
    } else {
        std::cout << "Success in adding message into offline databse || LINE 51\n";
        // Clear the execution result.
        PQclear(result);
    }
}

void deleteOfflineMessages(std::string user, PGconn *conn) {

    const std::string statement = "deleteOfflineMessage";

    // creates a array of character to hold parameters
    const char *parameterValues[1];
    parameterValues[0] = user.c_str();

    // paramLengths: An array of lengths for binary parameters. For text parameters, set to 0 or NULL.
    int paramLengths[1] = {0}; // 0 indicates null-terminated string

    // paramFormats: An array indicating format (0 for text, 1 for binary). We're using text.
    int paramFormats[1] = {0};

    // PQexecPrepared(conn, statement_name, num_params, param_values, param_lengths, param_formats, result_format)
    // - conn: The database connection.
    // - stmt_name.c_str(): The name of the prepared statement to execute.
    // - 1: The number of parameters being passed.
    // - paramValues: The array of parameter values.
    // - paramLengths: The array of parameter lengths.
    // - paramFormats: The array of parameter formats.
    // - 0: The desired format for the results (0 for text, 1 for binary).
    PGresult *result = PQexecPrepared(conn, statement.c_str(), 1, parameterValues, paramLengths, paramFormats, 0);

    // LOGGING
    if (PQresultStatus(result) != PGRES_COMMAND_OK) {
        std::cerr << "Execution of prepared statement failed: " << PQerrorMessage(conn) << std::endl;
        PQclear(result);
        PQfinish(conn);
    } else {
        std::cout << "Success in deleting message from offline databse || LINE 99\n";
        // Clear the execution result.
        PQclear(result);
    }
}

int loadOfflineMessages(std::string user, PGconn *conn) {
    const std::string statement = "getOfflineMessages";
    // creates a array of character to hold parameters
    const char *parameterValues[1];
    parameterValues[0] = user.c_str();

    // paramLengths: An array of lengths for binary parameters. For text parameters, set to 0 or NULL.
    int paramLengths[1] = {0}; // 0 indicates null-terminated string

    // paramFormats: An array indicating format (0 for text, 1 for binary). We're using text.
    int paramFormats[1] = {0};

    // PQexecPrepared(conn, statement_name, num_params, param_values, param_lengths, param_formats, result_format)
    // - conn: The database connection.
    // - stmt_name.c_str(): The name of the prepared statement to execute.
    // - 1: The number of parameters being passed.
    // - paramValues: The array of parameter values.
    // - paramLengths: The array of parameter lengths.
    // - paramFormats: The array of parameter formats.
    // - 0: The desired format for the results (0 for text, 1 for binary).
    PGresult *result = PQexecPrepared(conn, statement.c_str(), 1, parameterValues, paramLengths, paramFormats, 0);

    // logging
    if (PQresultStatus(result) != PGRES_TUPLES_OK) {
        std::cerr << "Execution of prepared statement failed: " << PQerrorMessage(conn) << std::endl;
        PQclear(result);
        PQfinish(conn);
    } else {
        int num_rows = PQntuples(result);
        // LOGGING
        std::cout << "SEARCHING FOR OFFLINE MESSAGES\n";
        if (num_rows > 0) {
            for (int i = 0; i < num_rows; i++) {
                std::cout << "MESSAGE NUMBER " << i + 1 <<  ": " << PQgetvalue(result, i, 0) << "\n";
                send(userToSocketDictionary[user], PQgetvalue(result, i, 0), strlen(PQgetvalue(result, i, 0)), 0);
            }
            return 1;
        } else {
            std::cout << "NO MESSAGE SENT TO : " << user << std::endl;
            return 0;
        }

        // 7. Clear the execution result.
        PQclear(result);
    }
}

void handleClients(SOCKET clientSocket, PGconn *conn) {
    char buffer[1024];
    std::string receiver;
    std::string sender;

    while (true) {
        // Whatever is sent through the client socket is saved to buffer data structure and saved to bytresReceived data
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) break; // error occured

        // Gets rid of garbage information
        buffer[bytesReceived] = '\0';
        // converts char to string
        std::string bufferString(buffer);
        std::cout << "Client says: " << bufferString << "\n";

        // if message includes logging user credentials
        if (bufferString.find("LOGGEDIN# = ") != std::string::npos) {
            //logging
            std::cout << "Storing user " << bufferString.substr(12) << "\n";

            // adds user client to a dictionary {name:socket}
            userToSocketDictionary[bufferString.substr(12)] = clientSocket;

            // add loading offline messages here
            int resultFromLoading = loadOfflineMessages(bufferString.substr(12), conn);

            // if offline messages was found for current user
            if (resultFromLoading == 1) {
                // deletes the offline messages
                deleteOfflineMessages(bufferString.substr(12), conn);
            }
        } else if (bufferString.find("LOGGEDOUT# = ") != std::string::npos){
            // LOGGING
            std::cout << "Removing user from server lists: USER: " << bufferString.substr(13) << "\n";

            // removes user client from  dictionary {name:socket}
            size_t RS = userToSocketDictionary.erase(bufferString.substr(13));
            if (RS > 0) {
                std::cout << "Successfully removed user from server, USER: " << bufferString.substr(13) << "\n";
            } else {
                std::cerr << "No user found, something went wrong || LINE 161" << "\n";
            }

        } else { // regular messages
            // getting the receiver's name || RECEIVER: ####;
            size_t lastEndingIndex = bufferString.rfind(";");
            size_t receiverIndex = bufferString.find("RECEIVER: ") + 10;
            receiver = bufferString.substr(receiverIndex, lastEndingIndex - receiverIndex);

            // gets the sender's name
            size_t firstEndingIndex = bufferString.find(";");
            size_t senderIndex = bufferString.find("USER: ") + 6;
            sender = bufferString.substr(senderIndex, firstEndingIndex - senderIndex);

            // logging
            std::cout << "RECEIVER OF MESSAGE: \""<< bufferString << "\" IS " << receiver << "\n";
            std::cout << "SENDER OF MESSAGE: \"" << bufferString <<  "\" IS " << sender << "\n";

            std::lock_guard<std::mutex> lock(clientsMutex);
            // receiver found
            if (userToSocketDictionary.find(receiver) != userToSocketDictionary.end()){
                // sends message to target user
                send(userToSocketDictionary[receiver], buffer, bytesReceived, 0);
            } else { // receiver is not found AKA receiver is offline or does not exists
                // validate receiver exists in db

                // log
                std::cout << "USER IS OFFLINE, SENDING MESSAGE TO DATABASE FOR OFFLINE STORAGE || LINE 166\n";

                // inserts message into db to be sent to user after they log in
                insertOfflineMessage(sender, receiver, bufferString, conn);

            }

            // stores the message into database for message history
            storeMessage(sender, receiver, bufferString, conn);
        }
    }
}

int main() {
    // database connection
    PGconn *conn = PQconnectdb("host=localhost, port=1234 dbname=TSPChatApplication user=postgres password=Oscarsgyang123");
    if (PQstatus(conn) != CONNECTION_OK) {
        std::cerr << "Connection failed: " << PQerrorMessage(conn);
        PQfinish(conn);
        return 1;
    }
    std::cout << "Connected to PostgreSQL successfully!\n"; // status of connection to database


    // prepares all the statement need for later
    // PQprepare sends the query definition to the database. The database parses and optimizes it.
    std::string statement = "getOfflineMessages";
    std::string query = "SELECT messagecontent FROM offlinemessages WHERE receiver = $1;" ;
    PGresult *resultPrepare = PQprepare(conn, statement.c_str(), query.c_str(), 1, NULL); // 1 = number of parameters, NULL = parameter types (let DB infer)

    // unsuccessful statement preparations
    if (PQresultStatus(resultPrepare) != PGRES_COMMAND_OK) {
        std::cerr << "Failed to prepare statement '" << statement << "': " << PQerrorMessage(conn) << std::endl;
        PQclear(resultPrepare);
        PQfinish(conn);
    } else {
        // successful statement preparation
        std::cout << "Statement '" << statement << "' prepared successfully.\n";
        PQclear(resultPrepare); // Always clear the result of PQprepare
    }

    // loads deleteOfflineMessage statement
    // PQprepare sends the query definition to the database. The database parses and optimizes it.
    statement = "deleteOfflineMessage";
    query = "DELETE FROM offlinemessages WHERE receiver = $1;" ;
    resultPrepare = PQprepare(conn, statement.c_str(), query.c_str(), 1, NULL); // 1 = number of parameters, NULL = parameter types (let DB infer)

    // unsuccessful statement preparations
    if (PQresultStatus(resultPrepare) != PGRES_COMMAND_OK) {
        std::cerr << "Failed to prepare statement '" << statement << "': " << PQerrorMessage(conn) << std::endl;
        PQclear(resultPrepare);
        PQfinish(conn);
    } else {
        // successful statement preparation
        std::cout << "Statement '" << statement << "' prepared successfully.\n";
        PQclear(resultPrepare); // Always clear the result of PQprepare
    }

    // prepares the statement of inserting offline messages into databases
    statement = "insertOfflineMessage";
    query = "INSERT INTO offlinemessages (sender, receiver, messagecontent) VALUES ($1, $2, $3)";

    // 3 = number of parameters, NULL = parameter types (let DB infer), prepares the results into conn to be used
    resultPrepare = PQprepare(conn, statement.c_str(), query.c_str(), 3, NULL);

    // logging for successful statement preparation
    if (PQresultStatus(resultPrepare) != PGRES_COMMAND_OK) {
        std::cerr << "Failed to prepare statement '" << statement << "': " << PQerrorMessage(conn) << std::endl;
        PQclear(resultPrepare);
        PQfinish(conn);
    } else {
        // successful statement preparations
        std::cout << "Statement: '" << statement << "' prepared successfully.\n";
        PQclear(resultPrepare); // Always clear the result of PQprepare
    }

    // prepares the statement of inserting messages into databases
    statement = "storeMessage";
    query = "INSERT INTO messagehistory (sender, receiver, messagecontent, timestamp) VALUES ($1, $2, $3, $4)";
    resultPrepare = PQprepare(conn, statement.c_str(), query.c_str(), 4, NULL);

    // logging for successful statement preparation
    if (PQresultStatus(resultPrepare) != PGRES_COMMAND_OK) {
        std::cerr << "Failed to prepare statement '" << statement << "': " << PQerrorMessage(conn) << std::endl;
        PQclear(resultPrepare);
        PQfinish(conn);
    } else {
        // successful statement preparations
        std::cout << "Statement: '" << statement << "' prepared successfully.\n";
        PQclear(resultPrepare); // Always clear the result of PQprepare
    }

    // starts WSADATA api
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    // Creates a IPV4, organized stream socket with default protocol
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Sets the IPV4 server address at port 12345, open to any IP address
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Binds the socket to this address
    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));

    //  initiliazes the server socket for 1 client
    listen(serverSocket, 1);

    // start  the server socket to wait for a client connection
    std::cout << "Server started. Waiting for clients...\n";

    while (true) {
        SOCKET clientSocket = accept(serverSocket, nullptr
            , nullptr);
        {
            std::lock_guard<std::mutex> lock(clientsMutex);
            clients.push_back(clientSocket);
        }
        std::thread(handleClients, clientSocket, conn).detach(); // starts the handling of client in a thread
        std::cout << "Client connected\n";
    }
    WSACleanup();
    return 0;
}