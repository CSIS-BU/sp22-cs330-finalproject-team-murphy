#include<stdio.h>
#include<string.h>	
#include<sys/socket.h>
#include<arpa/inet.h>	
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/types.h>
#include<netdb.h>
#include<netinet/in.h>
#include<time.h>

#include <random>
#include <ctime>

#define PORT 80
#define QUEUE 5
#define BUFFER_SIZE 2000

int Turn(int newClient, char buffer [BUFFER_SIZE], int errCnt);
winner CompTurn(int newClient, char buffer[BUFFER_SIZE], int gamestate[]);
winner HumanTurn(int newClient, char buffer[BUFFER_SIZE], int gamestate[]);
winner CheckWin(int newClient, char buffer[BUFFER_SIZE], int gamestate[]);
void Victor(int newClient, char buffer[BUFFER_SIZE], int win);
void BoardState(int newClient, char buffer[BUFFER_SIZE], int gamestate[]);
void FinalBoardState(int newClient, char buffer[BUFFER_SIZE], int gamestate[]);

int main(int argc, char *argv[])
{
	int sock;
	int clientSock;
	int newClient;
	int c;
	int readSize;
	struct sockaddr_in server;
	struct client;
//	char contents[2000];

	//make socket
	sock = socket(AF_INET , SOCK_STREAM , 0);
	if (sock == -1)
	{
		printf("socket failed");
	}
	puts("created socket");
	
	//get socket address
	bzero((char*)&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( PORT );
	
	if(bind(sock,(struct sockaddr *)&server, sizeof(server)) < 0)
	{
		perror("bind failed");
		return 1;
	}
	puts("binding succeeded");
	
	listen(sock, QUEUE);//Multiple Running Games
	
	//get connection
	puts("looking for client");
	c = sizeof(struct sockaddr_in);
	
	//Create Constant Server
	while (1)
	{
		//accept connection
		newClient = accept(sock, (struct sockaddr*)&client, (socklen_t*)&c);
		if (newClient < 0)
		{
			perror("client not accepted");
			close(newClient);
		}
		puts("client accepted");

		// Accepts Multiple Clients
		pid = fork();
		if (pid > 0)
		{
			close(newClient);
		}
		else if (pid == 0)
		{
			close(clientSock);


			// Tic-Tac-Toe Functionality
			mt19937 mt(time(nullptr));
			struct winner { int check; int player; };

			char buffer [BUFFER_SIZE];

            int gameState[10] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, NULL };
            winner victor;
            victor.check = 0; //false
            victor.player = 2;
            int errCnt = 0;
            int starter = Turn(newClient, buffer [BUFFER_SIZE], errCnt);
            char playerSymbol[] = "Player = X, AI = O\n";

            if (starter == '3')
            {
                int ran = mt() % 2 + 1;
                switch (ran)
                {
                case 1:          //setting cases to equal the expected outputs seems to keep things stable
                    victor = CompTurn(newClient, buffer[BUFFER_SIZE], gameState);
                    break;

                case 2:
                    victor = HumanTurn(newClient, buffer[BUFFER_SIZE], gameState);
                    break;
                }
            }
            switch (starter)
            {
            case '1':          //setting cases to equal the expected outputs seems to keep things stable
                victor = CompTurn(newClient, buffer[BUFFER_SIZE], gameState);
                break;

            case '2':
                victor = HumanTurn(newClient, buffer[BUFFER_SIZE], gameState);
                break;
            }
            Victor(newClient, buffer[BUFFER_SIZE], victor.player);
		}
	}


	
	//get and reply to message
	//while((readSize = recv(clientSock, contents, 2000, 0)) > 0 )
	//{
	//	//strcpy(contents, "server speaking");
	//	//send(clientSock, contents, 3, 0);
	//	write(clientSock, contents, strlen(contents));
	//}
	
	if(readSize == 0)
	{
		puts("client disconnected");
		fflush(stdout);
	}
	else if(readSize == -1)
	{
		perror("no data/connection failed");
	}

    close(newClient);
	return 0;
}

int Turn(int newClient, char buffer [BUFFER_SIZE], int errCnt)
{
    char start = 'z';       //setting this to a char prevented the string error
    size_t length = 0;
    errCnt++;
    char startingPlayer[] = "Who will go first? 1 = Ai; 2 = Player; 3 = Random\n";
    char invalidInput[] = "Invalid Input. Type Again.\n";
    send(newClient, startingPlayer, strlen(startingPlayer), 0);

    while (start != '1' && start != '2' && start != '3')
    {
        while ((length = recv(newClient, buffer, sizeof(buffer), 0) != 1))
        {
            errCnt++;
            // send(newClient, invalidInput, strlen(invalidInput), 0);
            // temp fix to write to buffer?
             size_t invalidInputLen = sprintf(buf, invalidInput, 1);
             send(newClient, buf, invalidInputLen, 0);

            if (errCnt >= 10)
            {
                close(newClient);
                exit(1491149029);
            }
        }
        // Read first character client sends back
        start = buffer[0];
    }

    //if (start == '1' || start == '2' || start == '3')
    //{
        return start;
    //}
    //else
    //{
    //    cout << "Invalid Input. Type Again.\n";
    //    Turn(errCnt);
    //}
}

winner CompTurn(int newClient, char buffer[BUFFER_SIZE], int gamestate[])
{
    int i = 0;
    int n = 3;
    int move;
    winner cvictor;
    cvictor.check = 0; //false
    cvictor.player = 2;
    winner test;
    test.check = 0; //false
    test.player = 2;
    move = mt() % 9;

    if (gamestate[move] == 0 || gamestate[move] == 1)
    {
        cvictor = CompTurn(newClient, buffer[BUFFER_SIZE], gamestate);
    }
    else
    {
        gamestate[move] = 0;
        test = CheckWin(newClient, buffer[BUFFER_SIZE], gamestate);
        if (test.check == 0)
        {
            cvictor = test;
            char finalBoardState[] = "Final Board State\n";
//            size_t finalBoardStateLen = sprintf(buf, finalBoardState, 1);
            send(newClient, finalBoardState, strlen(finalBoardState), 0);
//            cout << "Final Board State\n";
            FinalBoardState(newClient, buffer[BUFFER_SIZE], gamestate);
            return cvictor;
        }
        cvictor = HumanTurn(newClient, buffer[BUFFER_SIZE], gamestate);
    }
    return cvictor;
}

winner HumanTurn(int newClient, char buffer[BUFFER_SIZE], int gamestate[])
{
    char moveholder;
    int movetest;
    int move;
    winner hvictor;
    hvictor.check = false;
    hvictor.player = 2;
    winner test;
    test.check = false;
    test.player = 2;
    BoardState(newClient, buffer[BUFFER_SIZE], gamestate);

    while (1)
    {
        char makeAMove[] = "Make a Move 1-9\n";
//        cout << "Make a Move 1-9\n";
//        cin >> moveholder;
        int movetest = (int)moveholder;
        if (movetest < 49 || movetest > 57)
        {
            char invalidInput[] = "Invalid Input. Type Again.\n";
            send(newClient, startingPlayer, strlen(startingPlayer), 0);
//            cout << "Invalid input, try again.\n";
            BoardState(newClient, buffer[BUFFER_SIZE], gamestate);
            // https://www.cplusplus.com/forum/beginner/48568/
//            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            move = movetest - '0';
//            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }

    move--;

    if (gamestate[move] == 0 || gamestate[move] == 1)
    {
        char moveMade[] = "Move Already Made\n";
//        cout << "Move Already Made\n";
        hvictor = HumanTurn(newClient, buffer[BUFFER_SIZE], gamestate);
    }
    else
    {
        gamestate[move] = 1;
        test = CheckWin(newClient, buffer[BUFFER_SIZE], gamestate);
        if (test.check)
        {
            hvictor = test;
            char finalBoardState[] = "Final Board State\n";
//            cout << "Final Board State\n";
            FinalBoardState(newClient, buffer[BUFFER_SIZE], gamestate);
            return hvictor;
        }
        hvictor = CompTurn(newClient, buffer[BUFFER_SIZE], gamestate);
    }
    return hvictor;
}

void BoardState(int newClient, char buffer[BUFFER_SIZE], int gamestate[])
{
    int i = 0;
    int n = 3;
    int p = 0;
    char currentBoard[] = "Current Board\n";
    char gamestateReplica[15];
//    cout << "Current Board\n";
    while (n < 10)
    {
        for (i; i < n; i++)
        {
            switch (gamestate[i])
            {
            case 0:
//                cout << "O";
                gamestateReplica[i + 2 * p] = 'O';
                break;
            case 1:
//                cout << "X";
                gamestateReplica[i + 2 * p] = 'X';
                break;
            case 2:
//                cout << "|";
                gamestateReplica[i + 2 * p] = '|';
                break;
            }
        }
        gamestateReplica[i + 2 * p + 1] = '\n';
        p += 1;
//        n += 3;
//        cout << "\n";
    }
}

void FinalBoardState(int newClient, char buffer[BUFFER_SIZE], int gamestate[])
{
    int i = 0;
    int n = 3;
    //    cout << "Current Board\n";
//    char currentBoard[] = "Current Board\n";
    char gamestateReplica[10];
    while (n < 10)
    {
        for (i; i < n; i++)
        {
            switch (gamestate[i])
            {
            case 0:
                cout << "O";
                break;
            case 1:
                cout << "X";
                break;
            case 2:
                cout << "|";
                break;
            }
        }
        n += 3;
        cout << "\n";
    }
}

winner CheckWin(int newClient, char buffer[BUFFER_SIZE], int gamestate[])
{
    winner victor;
    victor.check = 0; //false
    victor.player = 2;
    // Comp Horizontal Test
    if ((gamestate[0] == 0 && gamestate[1] == 0 && gamestate[2] == 0) || (gamestate[3] == 0 && gamestate[4] == 0 && gamestate[5] == 0) || (gamestate[6] == 0 && gamestate[7] == 0 && gamestate[8] == 0))
    {
        victor.check = 1; //true
        victor.player = 0;
    }
    // Comp Vertical Test
    else if ((gamestate[0] == 0 && gamestate[3] == 0 && gamestate[6] == 0) || (gamestate[1] == 0 && gamestate[4] == 0 && gamestate[7] == 0) || (gamestate[2] == 0 && gamestate[5] == 0 && gamestate[8] == 0))
    {
        victor.check = 1; //true
        victor.player = 0;
    }
    // Comp Diagonal Test
    else if ((gamestate[0] == 0 && gamestate[4] == 0 && gamestate[8] == 0) || (gamestate[2] == 0 && gamestate[4] == 0 && gamestate[6] == 0))
    {
        victor.check = 1; //true
        victor.player = 0;
    }
    // Human Horizontal Test
    else if ((gamestate[0] == 1 && gamestate[1] == 1 && gamestate[2] == 1) || (gamestate[3] == 1 && gamestate[4] == 1 && gamestate[5] == 1) || (gamestate[6] == 1 && gamestate[7] == 1 && gamestate[8] == 1))
    {
        victor.check = 1; //true
        victor.player = 1;
    }
    // Human Vertical Test
    else if ((gamestate[0] == 1 && gamestate[3] == 1 && gamestate[6] == 1) || (gamestate[1] == 1 && gamestate[4] == 1 && gamestate[7] == 1) || (gamestate[2] == 1 && gamestate[5] == 1 && gamestate[8] == 1))
    {
        victor.check = 1; //true
        victor.player = 1;
    }
    // Human Diagonal Test
    else if ((gamestate[0] == 1 && gamestate[4] == 1 && gamestate[8] == 1) || (gamestate[2] == 1 && gamestate[4] == 1 && gamestate[6] == 1))
    {
        victor.check = 1; //true
        victor.player = 1;
    }
    // Draw Test
    else
    {
        int DrawTest = 1; //true
        for (int i = 0; i < 9; i++)
        {
            if (gamestate[i] == 2)
            {
                DrawTest = 0; //false
            }
        }
        if (DrawTest == 1)
        {
            char finalBoardState[] = "Final Board State\n";
//            cout << "Final Board State\n";
            FinalBoardState(newClient, buffer[BUFFER_SIZE], gamestate);
            char draw[] = "Final Board State\n";
//            cout << "The Game is a Draw.\n";
            exit(NULL);
        }
    }
    return victor;
}

void Victor(int newClient, char buffer[BUFFER_SIZE], int win)
{
    switch (win)
    {
    case 0:
        cout << "You Lose!\n";
        break;
    case 1:
        cout << "You Win!\n";
        break;
    }
}