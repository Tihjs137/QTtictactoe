#include "mainwindow.h"
#include "ui_mainwindow.h"

int Turn = 0;

QString board[3][3] = {{"","",""}, {"", "", ""}, {"", "", ""}};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::makeMove()
{
    bool exit = false;
    int bestScore = -99999;
    int move = -1;

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(board[i][j] == "")
            {
                board[i][j] = "O";
                int score = minimax(board, 0, "X");
                board[i][j] = "";

                if(score > bestScore)
                {
                    bestScore = score;
                    move = i+j*3;

                }



            }
        }
    }

    //ui->label->setNum(bestScore);
    write(move);
}

int MainWindow::minimax(QString myBoard[3][3], int depth, QString isMaximizing)
{
    QString result = checkWinner(myBoard);
    if(result != "-1")
    {
        //disableAll();
        //ui->label->setText(checkWinner() + " Is the winner");
        if(result == "O")
        {
            return 10;
        }
        else if(result == "X")
        {
            return -10;
        }
        else
        {
            return 0;
        }

    }

    if (isMaximizing == "O")
    {
        int bestScore = -999;
        for (int i = 0; i < 3; i++)
        {
          for (int j = 0; j < 3; j++)
          {
            // Is the spot available?
            if (myBoard[i][j] == "")
            {
              myBoard[i][j] = "O";
              int score = minimax(myBoard, depth + 1, "X");
              myBoard[i][j] = "";
              bestScore = qMax(score, bestScore);
            }
          }
        }
        return bestScore;
    }

    else
    {
        int bestScore = 999;
        for (int i = 0; i < 3; i++)
        {
          for (int j = 0; j < 3; j++)
          {
            // Is the spot available?
            if (myBoard[i][j] == "")
            {
              myBoard[i][j] = "X";
              int score = minimax(myBoard, depth + 1, "O");
              myBoard[i][j] = "";
              bestScore = qMin(score, bestScore);
            }
          }
        }
        return bestScore;
      }


}

void MainWindow::write(int index)
{
    QString placeChar;
    if(Turn % 2)
    {
        placeChar = "O";
    }
    else
    {
        placeChar = "X";
    }

    Turn++;
    switch(index)
    {
        case 0:
            board[0][0] = placeChar;
            ui->pushButton->setText(placeChar);
            ui->pushButton->setDisabled(true);
            break;
        case 1:
            board[1][0] = placeChar;
            ui->pushButton_2->setText(placeChar);
            ui->pushButton_2->setDisabled(true);
            break;
        case 2:
            board[2][0] = placeChar;
            ui->pushButton_3->setText(placeChar);
            ui->pushButton_3->setDisabled(true);
            break;
        case 3:
            board[0][1] = placeChar;
            ui->pushButton_4->setText(placeChar);
            ui->pushButton_4->setDisabled(true);
            break;
        case 4:
            board[1][1] = placeChar;
            ui->pushButton_5->setText(placeChar);
            ui->pushButton_5->setDisabled(true);
            break;
        case 5:
            board[2][1] = placeChar;
            ui->pushButton_6->setText(placeChar);
            ui->pushButton_6->setDisabled(true);
            break;
        case 6:
            board[0][2] = placeChar;
            ui->pushButton_7->setText(placeChar);
            ui->pushButton_7->setDisabled(true);
            break;
        case 7:
            board[1][2] = placeChar;
            ui->pushButton_8->setText(placeChar);
            ui->pushButton_8->setDisabled(true);
            break;
        case 8:
            board[2][2] = placeChar;
            ui->pushButton_9->setText(placeChar);
            ui->pushButton_9->setDisabled(true);
            break;
    }


    if(checkWinner() != "0")
    {
        disableAll();
        ui->label->setText(checkWinner() + " Is the winner");
    }

}

QString MainWindow::checkWinner()
{
    //Horizontaal
    if(ui->pushButton->text() != "" && ui->pushButton->text() == ui->pushButton_2->text() && ui->pushButton_2->text() == ui->pushButton_3->text())
    {
        return ui->pushButton->text();
    }
    else if(ui->pushButton_4->text() != "" && ui->pushButton_4->text() == ui->pushButton_5->text() && ui->pushButton_5->text() == ui->pushButton_6->text())
    {
        return ui->pushButton_4->text();
    }
    else if(ui->pushButton_7->text() != "" && ui->pushButton_7->text() == ui->pushButton_8->text() && ui->pushButton_8->text() == ui->pushButton_9->text())
    {
        return ui->pushButton_7->text();
    }

    //Verticaal
    if(ui->pushButton->text() != "" && ui->pushButton->text() ==  ui->pushButton_4->text() && ui->pushButton_4->text() == ui->pushButton_7->text())
    {
        return ui->pushButton->text();
    }
    else if(ui->pushButton_2->text() != "" && ui->pushButton_2->text() == ui->pushButton_5->text() && ui->pushButton_5->text() == ui->pushButton_8->text())
    {
        return ui->pushButton_2->text();
    }
    else if(ui->pushButton_3->text() != "" && ui->pushButton_3->text() == ui->pushButton_6->text() && ui->pushButton_6->text() == ui->pushButton_9->text())
    {
        return ui->pushButton_3->text();
    }

    //Diagonaal
    if(ui->pushButton->text() != "" && ui->pushButton->text() == ui->pushButton_5->text() && ui->pushButton_5->text() == ui->pushButton_9->text())
    {
        return ui->pushButton_5->text();
    }
    else if(ui->pushButton_7->text() != "" && ui->pushButton_7->text() == ui->pushButton_5->text() && ui->pushButton_5->text() == ui->pushButton_3->text())
    {
        return ui->pushButton_5->text();
    }

    if(Turn == 9)
    {
        disableAll();
        ui->label->setText("Tie!");
    }

    return "0";
}

QString MainWindow::checkWinner(QString myBoard[3][3])
{
    //Horizontaal
    if(myBoard[0][0] != "" && myBoard[0][0] == myBoard[1][0] && myBoard[1][0] == myBoard[2][0])
    {
        return myBoard[0][0];
    }
    else if(myBoard[0][1] != "" && myBoard[0][1] == myBoard[1][1] && myBoard[1][1] == myBoard[2][1])
    {
        return myBoard[0][1];
    }
    else if(myBoard[0][2] != "" && myBoard[0][2] == myBoard[1][2] && myBoard[1][2] == myBoard[2][2])
    {
        return myBoard[0][2];
    }

    //Verticaal
    if(myBoard[0][0] != "" && myBoard[0][0] == myBoard[0][1] && myBoard[0][1] == myBoard[0][2])
    {
        return myBoard[0][0];
    }
    else if(myBoard[1][0] != "" && myBoard[1][0] == myBoard[1][1] && myBoard[1][1] == myBoard[1][2])
    {
        return myBoard[1][0];
    }
    else if(myBoard[2][0] != "" && myBoard[2][0] == myBoard[2][1] && myBoard[2][1] == myBoard[2][2])
    {
        return myBoard[2][0];
    }

    //Diagonaal
    if(myBoard[0][0] != "" && myBoard[0][0] == myBoard[1][1] && myBoard[1][1] == myBoard[2][2])
    {
        return myBoard[0][0];
    }
    else if(myBoard[0][2] != "" && myBoard[0][2] == myBoard[1][1] && myBoard[1][1] == myBoard[2][0])
    {
        return myBoard[0][2];
    }
    else if(myBoard[0][0] != "" && myBoard[0][1] != "" && myBoard[0][2] != "" && myBoard[1][0] != ""
            && myBoard[1][1] != "" && myBoard[1][2] != "" && myBoard[2][0] != "" && myBoard[2][1] != "" && myBoard[2][2] != "" )
    {
        return "0";
    }

    return "-1";
}

void MainWindow::disableAll()
{
    Turn = 0;
    ui->pushButton->setDisabled(true);
    ui->pushButton_2->setDisabled(true);
    ui->pushButton_3->setDisabled(true);
    ui->pushButton_4->setDisabled(true);
    ui->pushButton_5->setDisabled(true);
    ui->pushButton_6->setDisabled(true);
    ui->pushButton_7->setDisabled(true);
    ui->pushButton_8->setDisabled(true);
    ui->pushButton_9->setDisabled(true);
}

void MainWindow::on_pushButton_clicked()
{
    write(0);
    makeMove();
}

void MainWindow::on_pushButton_2_clicked()
{
    write(1);
    makeMove();
}

void MainWindow::on_pushButton_3_clicked()
{
    write(2);
    makeMove();
}

void MainWindow::on_pushButton_4_clicked()
{
    write(3);
    makeMove();
}

void MainWindow::on_pushButton_5_clicked()
{
    write(4);
    makeMove();
}

void MainWindow::on_pushButton_6_clicked()
{
    write(5);
    makeMove();
}

void MainWindow::on_pushButton_7_clicked()
{
    write(6);
    makeMove();
}

void MainWindow::on_pushButton_8_clicked()
{
    write(7);
    makeMove();
}

void MainWindow::on_pushButton_9_clicked()
{
    write(8);
    makeMove();
}

void MainWindow::on_pushButton_10_clicked()
{
    //reset the board
    ui->pushButton->setText("");
    ui->pushButton->setDisabled(false);

    ui->pushButton_2->setText("");
    ui->pushButton_2->setDisabled(false);

    ui->pushButton_3->setText("");
    ui->pushButton_3->setDisabled(false);

    ui->pushButton_4->setText("");
    ui->pushButton_4->setDisabled(false);

    ui->pushButton_5->setText("");
    ui->pushButton_5->setDisabled(false);

    ui->pushButton_6->setText("");
    ui->pushButton_6->setDisabled(false);

    ui->pushButton_7->setText("");
    ui->pushButton_7->setDisabled(false);

    ui->pushButton_8->setText("");
    ui->pushButton_8->setDisabled(false);

    ui->pushButton_9->setText("");
    ui->pushButton_9->setDisabled(false);

    ui->label->setText("");

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            board[i][j] = "";
        }
    }

    Turn = 0;
}
