using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using Windows.UI.Xaml.Shapes;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace Connect4
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        Ellipse[][] ellipse = new Ellipse[7][];
        int[][] gameBoard = new int[7][];
        private bool playerTurn;
        private int redWins, blueWins, tie;
        public MainPage()
        {
            InitializeComponent();
            for (int i = 0; i < 7; ++i)
            {
                gameBoard[i] = new int[6];
                redWins = 0;
                blueWins = 0;
                tie = 0;
                ellipse[i] = new Ellipse[6];
                for (int j = 0; j < 6; ++j)
                {
                    gameBoard[i][j] = 0;
                    ellipse[i][j] = new Ellipse();
                    ellipse[i][j].Fill = new SolidColorBrush(Colors.Black);
                    Grid.SetRow(ellipse[i][j], j + 2);
                    Grid.SetColumn(ellipse[i][j], i);
                    ThisGrid.Children.Add(ellipse[i][j]);
                }
            }
            Desc.Text = "Blue Player's Turn";
            Red.Text = "Red wins: " + redWins;
            Blue.Text = "Blue wins: " + blueWins;
            Ties.Text = "Ties: " + tie;
        }

        private void SetSize(object sender, RoutedEventArgs e)
        {
                for (int i = 0; i < 7; ++i)
                {
                for (int j = 0; j < 6; ++j)
                {
                    int min;
                    if (ActualWidth < ActualHeight)
                        min = (int)ActualWidth / 7 - 10;
                    else min = (int)ActualHeight / 8 - 10;
                    ellipse[i][j].Width = min;
                    ellipse[i][j].Height = min;
                    ellipse[i][j].VerticalAlignment = VerticalAlignment.Center;
                    ellipse[i][j].HorizontalAlignment = HorizontalAlignment.Center;
                }
            }
        }

        private void PreventButtons()
        {
            Replay.Visibility = Visibility.Visible;
            Row1.IsEnabled = false;
            Row2.IsEnabled = false;
            Row3.IsEnabled = false;
            Row4.IsEnabled = false;
            Row5.IsEnabled = false;
            Row6.IsEnabled = false;
            Row7.IsEnabled = false;
        }

        private void Calculate(object sender, RoutedEventArgs e)
        {
            Button b = (Button) sender;
            int column = Grid.GetColumn(b);
            for (int i = 5; i > -1; --i)
            {
                if (gameBoard[column][i] == 0)
                {
                    if (playerTurn)
                    {
                        ellipse[column][i].Fill = new SolidColorBrush(Colors.Red);
                        gameBoard[column][i] = 1;
                        Desc.Text = "Blue Player's Turn";
                    }
                    else
                    {
                        ellipse[column][i].Fill = new SolidColorBrush(Colors.Blue);
                        gameBoard[column][i] = 2;
                        Desc.Text = "Red Player's Turn";
                    }
                    playerTurn = !playerTurn;
                    break;
                }
            }

            for (int i = 0; i < 7; i++) {
                if (gameBoard[i][0] == 0)
                    break;
                if (i == 6)
                {
                    Desc.Text = "It's a tie!";
                    tie++;
                }
            }

            for (int i = 0; i < 7; i++)
                for (int j = 0; j < 3; j++) {
                    if (gameBoard[i][j] == gameBoard[i][j + 1] && gameBoard[i][j + 1] == gameBoard[i][j + 2] && gameBoard[i][j + 2] == gameBoard[i][j + 3] && gameBoard[i][j] != 0)
                    {
                        if (gameBoard[i][j] == 1)
                        {
                            Desc.Text = "Red wins!!";
                            redWins++;
                        }
                        else
                        {
                            Desc.Text = "Blue wins!!";
                            blueWins++;
                        }
                        PreventButtons();
                    }
                }
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 6; j++) {
                    if (gameBoard[i][j] == gameBoard[i + 1][j] && gameBoard[i + 1][j] == gameBoard[i + 2][j] && gameBoard[i + 2][j] == gameBoard[i + 3][j] && gameBoard[i][j] != 0) {
                        if (gameBoard[i][j] == 1) {
                            Desc.Text = "Red wins!!";
                            redWins++;
                        }
                        else {
                            Desc.Text = "Blue wins!!";
                            blueWins++;
                        }
                        PreventButtons();
                    }
                }
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 3; j++) {
                    if (gameBoard[i][j] == gameBoard[i + 1][j + 1] && gameBoard[i + 1][j + 1] == gameBoard[i + 2][j + 2] && gameBoard[i + 2][j + 2] == gameBoard[i + 3][j + 3] && gameBoard[i][j] != 0) {
                        if (gameBoard[i][j] == 1) {
                            Desc.Text = "Red wins!!";
                            redWins++;
                        }
                        else {
                            Desc.Text = "Blue wins!!";
                            blueWins++;
                        }
                        PreventButtons();
                    }
                }
            for (int i = 0; i < 4; i++)
                for (int j = 3; j < 6; j++) {
                    if (gameBoard[i][j] == gameBoard[i + 1][j - 1] && gameBoard[i + 1][j - 1] == gameBoard[i + 2][j - 2] && gameBoard[i + 2][j - 2] == gameBoard[i + 3][j - 3] && gameBoard[i][j] != 0) {
                        if (gameBoard[i][j] == 1) {
                            Desc.Text = "Red wins!!";
                            redWins++;
                        }
                        else {
                            Desc.Text = "Blue wins!!";
                            blueWins++;
                        }
                        PreventButtons();
                    }
                }
            if(Desc.Text == "It's a tie!")
                PreventButtons();
            Red.Text = "Red wins: " + redWins;
            Blue.Text = "Blue wins: " + blueWins;
            Ties.Text = "Ties: " + tie;
        }

        private void PlayAgain(object sender, RoutedEventArgs e)
        {
            for(int i = 0; i < 7; ++i)
                for (int j = 0; j < 6; ++j)
                {
                    gameBoard[i][j] = 0;
                    ellipse[i][j].Fill = new SolidColorBrush(Colors.Black);
                }
            Replay.Visibility = Visibility.Collapsed;
            Row1.IsEnabled = true;
            Row2.IsEnabled = true;
            Row3.IsEnabled = true;
            Row4.IsEnabled = true;
            Row5.IsEnabled = true;
            Row6.IsEnabled = true;
            Row7.IsEnabled = true;
            if (playerTurn)
                Desc.Text = "Red Player's Turn";
            else Desc.Text = "Blue Player's Turn";
        }
    }
}
