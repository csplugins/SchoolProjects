using System;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace CalcApp {
    public sealed partial class MainPage : Page {
        private double displayVal;
        private string str;
        private bool opLast;
        private bool equalsLast;
        private double storedNumber;
        private string op;
        public MainPage() {
            displayVal = 0;
            opLast = false;
            op = "";
            str = "0";
            InitializeComponent();
        }

        private void SetSize(object sender, RoutedEventArgs e) {
            //System.Diagnostics.Debug.WriteLine(this.ActualWidth);
            Value1.Width = ActualWidth / 3 - 15;
            Value2.Width = ActualWidth / 3 - 15;
            Value3.Width = ActualWidth / 3 - 15;
            Value4.Width = ActualWidth / 3 - 15;
            Value5.Width = ActualWidth / 3 - 15;
            Value6.Width = ActualWidth / 3 - 15;
            Value7.Width = ActualWidth / 3 - 15;
            Value8.Width = ActualWidth / 3 - 15;
            Value9.Width = ActualWidth / 3 - 15;
            Value0.Width = ActualWidth / 3 - 15;
            ValueSign.Width = ActualWidth / 3 - 15;
            ValuePeriod.Width = ActualWidth / 3 - 15;
            Display.Width = ActualWidth / 3 + 30;
            Display.Text = displayVal.ToString();
        }

        private void Value_Click(object sender, RoutedEventArgs e) {
            Button B = (Button)sender;
            string s = B.Content.ToString();
            if (s == "0" || s == "1" || s == "2" || s == "3" || s == "4" || s == "5" || s == "6" || s == "7" || s == "8" || s == "9") {
                if (opLast) {
                    str = "0";
                    opLast = false;
                    if (equalsLast) {
                        op = "";
                        equalsLast = false;
                    }
                }
                if (str.Length < 17) {
                    if (str == "0")
                        str = s;
                    else str += B.Content;
                }
                displayVal = Double.Parse(str);
                Display.Text = str;
            }
            else if (s == "CLR") {
                displayVal = 0;
                str = "0";
                storedNumber = 0;
                Display.Text = str;
            }
            else if (s == "+" || s == "-" || s == "x" || s == "÷") {
                op = s;
                storedNumber = displayVal;
                opLast = true;
                equalsLast = false;
            }
            else if (s == ".") {
                if (opLast) {
                    str = "0";
                    opLast = false;
                    if (equalsLast) {
                        op = "";
                        equalsLast = false;
                    }
                }
                if (!str.Contains(".")) {
                    str += ".";
                    Display.Text = str;
                }
            }
            else if (s == "±") {
                if (str[0] == '-') {
                    str = str.Substring(1, str.Length - 1);
                }
                else str = "-" + str;
                displayVal = Double.Parse(str);
                Display.Text = str;
            }
            else if (s == "=")
            {
                if (op == "")
                {
                    str = displayVal.ToString();
                    Display.Text = str;
                    opLast = true;
                    return;
                }
                if (!equalsLast) {
                    double swap = displayVal;
                    displayVal = storedNumber;
                    storedNumber = swap;
                }
                if (op == "+") {
                    displayVal += storedNumber;
                }
                else if (op == "-") {
                    displayVal -= storedNumber;
                }
                else if (op == "÷") {
                    displayVal /= storedNumber;
                }
                else if (op == "x") {
                    displayVal *= storedNumber;
                }
                str = displayVal.ToString();
                Display.Text = str;
                opLast = true;
                equalsLast = true;
            }
        }
    }
}
