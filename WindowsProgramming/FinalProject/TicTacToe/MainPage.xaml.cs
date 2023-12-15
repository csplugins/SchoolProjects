using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace TicTacToe
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        private bool player;
        private int xWins, oWins, tie, freeSpots;
        public MainPage()
        {
            InitializeComponent();
            player = true;
            xWins = 0;
            oWins = 0;
            tie = 0;
            freeSpots = 9;
            Desc.Text = "Player Turn: " + (player ? "X" : "O");
            X.Text = "X wins: " + xWins;
            O.Text = "O wins: " + oWins;
            Ties.Text = "Ties: " + tie;
        }

        private void DisableButtons(char c)
        {
            if (c == 'X')
                xWins++;
            else if (c == 'O')
                oWins++;
            else tie++;
            X.Text = "X wins: " + xWins;
            O.Text = "O wins: " + oWins;
            Ties.Text = "Ties: " + tie;

            Replay.Visibility = Visibility.Visible;
            TopLeft.IsEnabled = false;
            TopMiddle.IsEnabled = false;
            TopRight.IsEnabled = false;
            MiddleLeft.IsEnabled = false;
            MiddleMiddle.IsEnabled = false;
            MiddleRight.IsEnabled = false;
            BottomLeft.IsEnabled = false;
            BottomMiddle.IsEnabled = false;
            BottomRight.IsEnabled = false;
        }

        private void Calculate(object sender, RoutedEventArgs e)
        {
            Button b = (Button)sender;
            b.Content = player ? "X" : "O";
            b.IsEnabled = false;
            freeSpots--;
            player = !player;

            Desc.Text = "Player Turn: " + (player ? "X" : "O");
            if (freeSpots == 0)
            {
                Desc.Text = "Tie!";
                DisableButtons(Desc.Text[0]);
            }

            if (TopLeft.Content == TopMiddle.Content && TopMiddle.Content == TopRight.Content && TopLeft.Content != null)
            {
                Desc.Text = TopLeft.Content + " is the winner!!";
                DisableButtons(Desc.Text[0]);
            }
            if (MiddleLeft.Content == MiddleMiddle.Content && MiddleMiddle.Content == MiddleRight.Content && MiddleLeft.Content != null)
            {
                Desc.Text = MiddleLeft.Content + " is the winner!!";
                DisableButtons(Desc.Text[0]);
            }
            if (BottomLeft.Content == BottomMiddle.Content && BottomMiddle.Content == BottomRight.Content && BottomLeft.Content != null)
            {
                Desc.Text = BottomLeft.Content + " is the winner!!";
                DisableButtons(Desc.Text[0]);
            }
            if (TopLeft.Content == MiddleLeft.Content && MiddleLeft.Content == BottomLeft.Content && BottomLeft.Content != null)
            {
                Desc.Text = TopLeft.Content + " is the winner!!";
                DisableButtons(Desc.Text[0]);
            }
            if (TopMiddle.Content == MiddleMiddle.Content && MiddleMiddle.Content == BottomMiddle.Content && BottomMiddle.Content != null)
            {
                Desc.Text = TopMiddle.Content + " is the winner!!";
                DisableButtons(Desc.Text[0]);
            }
            if (TopRight.Content == MiddleRight.Content && MiddleRight.Content == BottomRight.Content && BottomRight.Content != null)
            {
                Desc.Text = TopRight.Content + " is the winner!!";
                DisableButtons(Desc.Text[0]);
            }
            if (TopLeft.Content == MiddleMiddle.Content && MiddleMiddle.Content == BottomRight.Content && BottomRight.Content != null)
            {
                Desc.Text = TopLeft.Content + " is the winner!!";
                DisableButtons(Desc.Text[0]);
            }
            if (TopRight.Content == MiddleMiddle.Content && MiddleMiddle.Content == BottomLeft.Content && BottomLeft.Content != null)
            {
                Desc.Text = TopRight.Content + " is the winner!!";
                DisableButtons(Desc.Text[0]);
            }
        }

        private void PlayAgain(object sender, RoutedEventArgs e)
        {
            TopLeft.Content = null;
            TopMiddle.Content = null;
            TopRight.Content = null;
            MiddleLeft.Content = null;
            MiddleMiddle.Content = null;
            MiddleRight.Content = null;
            BottomLeft.Content = null;
            BottomMiddle.Content = null;
            BottomRight.Content = null;
            TopLeft.IsEnabled = true;
            TopMiddle.IsEnabled = true;
            TopRight.IsEnabled = true;
            MiddleLeft.IsEnabled = true;
            MiddleMiddle.IsEnabled = true;
            MiddleRight.IsEnabled = true;
            BottomLeft.IsEnabled = true;
            BottomMiddle.IsEnabled = true;
            BottomRight.IsEnabled = true;
            freeSpots = 9;
            player = !player;
            Replay.Visibility = Visibility.Collapsed;
        }
    }
}
