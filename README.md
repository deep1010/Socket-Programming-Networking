-- Client and Server folders have the respective codes in their folders.
-- ./a.out in both the folders run the executable.
-- Run the server first and then the client to prevent error occurrences.
   Although, client side checks for the errors, incase the server isn't working as the time of connection.
-- The code is meant to send multiple files in a session.
-- Every time a file is sent, the client closes the socket and creates another one (non-persistent).
-- The client session closes on typing 'q' in the entire filename prompt.
-- All the error have been handled from socket creation to connection establishment and file not found.
-- The prompts are suggestive enough for the user to run the server and client system in their first trial.
-- Above were for the Q1 part wherein the implementation has been extended to work for the non-persistent part.
-- In Q2, some tweak are made in the for loop such that it works for the persistent connection.
-- In persistent connection, the client doesn't create a socket after every tranfer but uses the same connection
   to transfer multiple files.
-- Proper error handling has been done for both the codes, such as the mentioned below.
-- The prompts are intuitive enough for any new user and comments are made at some intervals in the code to enhance
   the readability of the code.

Errors handled:

-> Socket creation
-> Port attaching (forcibly)
-> Socket binding to the host and the port
-> Connection establishment
-> The file not found error is shown in the client end rather than the server side, because
   it's the client who need to know the correct name of the file.

Developer(s): Deep Patel(20161010) and Aanshul Sadaria(20161140) 
	      (International Institute of Information Technology, Hyderabad)
