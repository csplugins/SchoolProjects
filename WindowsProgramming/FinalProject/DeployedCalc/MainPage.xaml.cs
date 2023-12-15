using System;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace DeployedCalc
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page{
        public MainPage(){
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e){
            int show;
            int i = 1;
            Visibility[] CCC = { Visibility.Collapsed ,Visibility.Visible };
            if ((bool)Sin.IsChecked || (bool)Cos.IsChecked || (bool)Tan.IsChecked)
            {
                show = 1;
            }
            else show = 0;
            if ((bool)Sin.IsChecked)
            {
                Grid.SetColumn(SinT, i);
                ThisGrid.Children.Remove(SinT);
                ThisGrid.Children.Add(SinT);
                i++;
            }
            if ((bool)Cos.IsChecked)
            {
                Grid.SetColumn(CosT, i);
                ThisGrid.Children.Remove(CosT);
                ThisGrid.Children.Add(CosT);
                i++;
            }
            if ((bool)Tan.IsChecked)
            {
                Grid.SetColumn(TanT, i);
                ThisGrid.Children.Remove(TanT);
                ThisGrid.Children.Add(TanT);
                i++;
            }
            SinT.Visibility = CCC[Convert.ToInt32((bool)Sin.IsChecked)];
            CosT.Visibility = CCC[Convert.ToInt32((bool)Cos.IsChecked)];
            TanT.Visibility = CCC[Convert.ToInt32((bool)Tan.IsChecked)];
            Num1.Visibility = CCC[show];
            Result.Visibility = CCC[show];
            i = 1;
            if ((bool) SimpleAdd.IsChecked || (bool) SimpleSub.IsChecked || (bool) SimpleMult.IsChecked || (bool) SimpleDiv.IsChecked || (bool)SimplePow.IsChecked || (bool)SimpleMod.IsChecked)
            {
                show = 1;
            }
            else show = 0;
            if ((bool)SimpleAdd.IsChecked)
            {
                Grid.SetColumn(SimplePlus, i);
                ThisGrid.Children.Remove(SimplePlus);
                ThisGrid.Children.Add(SimplePlus);
                i++;
            }
            if ((bool)SimpleSub.IsChecked)
            {
                Grid.SetColumn(SimpleMinus, i);
                ThisGrid.Children.Remove(SimpleMinus);
                ThisGrid.Children.Add(SimpleMinus);
                i++;
            }
            if ((bool)SimpleMult.IsChecked)
            {
                Grid.SetColumn(SimpleMultiply, i);
                ThisGrid.Children.Remove(SimpleMultiply);
                ThisGrid.Children.Add(SimpleMultiply);
                i++;
            }
            if ((bool)SimpleDiv.IsChecked)
            {
                Grid.SetColumn(SimpleDivide, i);
                ThisGrid.Children.Remove(SimpleDivide);
                ThisGrid.Children.Add(SimpleDivide);
                i++;
            }
            if ((bool)SimplePow.IsChecked)
            {
                Grid.SetColumn(SimplePower, i);
                ThisGrid.Children.Remove(SimplePower);
                ThisGrid.Children.Add(SimplePower);
                i++;
            }
            if ((bool)SimpleMod.IsChecked)
            {
                Grid.SetColumn(SimpleModulous, i);
                ThisGrid.Children.Remove(SimpleModulous);
                ThisGrid.Children.Add(SimpleModulous);
                i++;
            }
            i = 1;
            if ((bool)ComplexAdd.IsChecked)
            {
                Grid.SetColumn(ComplexPlus, i);
                ThisGrid.Children.Remove(ComplexPlus);
                ThisGrid.Children.Add(ComplexPlus);
                i++;
            }
            if ((bool)ComplexSub.IsChecked)
            {
                Grid.SetColumn(ComplexMinus, i);
                ThisGrid.Children.Remove(ComplexMinus);
                ThisGrid.Children.Add(ComplexMinus);
                i++;
            }
            if ((bool)ComplexMult.IsChecked)
            {
                Grid.SetColumn(ComplexMultiply, i);
                ThisGrid.Children.Remove(ComplexMultiply);
                ThisGrid.Children.Add(ComplexMultiply);
                i++;
            }
            if ((bool)ComplexDiv.IsChecked)
            {
                Grid.SetColumn(ComplexDivide, i);
                ThisGrid.Children.Remove(ComplexDivide);
                ThisGrid.Children.Add(ComplexDivide);
                i++;
            }
            SimplePlus.Visibility = CCC[Convert.ToInt32((bool)SimpleAdd.IsChecked)];
            SimpleMinus.Visibility = CCC[Convert.ToInt32((bool)SimpleSub.IsChecked)];
            SimpleMultiply.Visibility = CCC[Convert.ToInt32((bool)SimpleMult.IsChecked)];
            SimpleDivide.Visibility = CCC[Convert.ToInt32((bool)SimpleDiv.IsChecked)];
            SimplePower.Visibility = CCC[Convert.ToInt32((bool)SimplePow.IsChecked)];
            SimpleModulous.Visibility = CCC[Convert.ToInt32((bool)SimpleMod.IsChecked)];
            SimpleNum1.Visibility = CCC[show];
            SimpleNum2.Visibility = CCC[show];
            SimpleResult.Visibility = CCC[show];

            if ((bool) ComplexAdd.IsChecked || (bool) ComplexSub.IsChecked || (bool) ComplexMult.IsChecked || (bool) ComplexDiv.IsChecked){
                show = 1;
            }
            else show = 0;
            ComplexPlus.Visibility = CCC[Convert.ToInt32((bool)ComplexAdd.IsChecked)];
            ComplexMinus.Visibility = CCC[Convert.ToInt32((bool)ComplexSub.IsChecked)];
            ComplexMultiply.Visibility = CCC[Convert.ToInt32((bool)ComplexMult.IsChecked)];
            ComplexDivide.Visibility = CCC[Convert.ToInt32((bool)ComplexDiv.IsChecked)];
            ComplexReal1.Visibility = CCC[show];
            ComplexImg1.Visibility = CCC[show];
            ComplexReal2.Visibility = CCC[show];
            ComplexImg2.Visibility = CCC[show];
            ComplexResult.Visibility = CCC[show];
        }
        
        private void Calculate(object sender, RoutedEventArgs e)
        {
            Button b = (Button)sender;
            if (b.Name == "SinT")
            {
                SimpleCalc s = new SimpleCalc();
                try
                {
                    Result.Text = "Result: " + s.sin(Convert.ToSingle(Num1.Text));
                }
                catch (FormatException)
                {
                    Result.Text = "Please Enter Valid Numbers";
                }
            }
            else if (b.Name == "CosT")
            {
                SimpleCalc s = new SimpleCalc();
                try
                {
                    Result.Text = "Result: " + s.cos(Convert.ToSingle(Num1.Text));
                }
                catch (FormatException)
                {
                    Result.Text = "Please Enter Valid Numbers";
                }
            }
            else if (b.Name == "TanT")
            {
                SimpleCalc s = new SimpleCalc();
                try
                {
                    Result.Text = "Result: " + s.tan(Convert.ToSingle(Num1.Text));
                }
                catch (FormatException)
                {
                    Result.Text = "Please Enter Valid Numbers";
                }
            }
            else if (b.Name == "SimplePlus") {
                SimpleCalc s = new SimpleCalc();
                try
                {
                    SimpleResult.Text = "Result: " + s.add(Convert.ToSingle(SimpleNum1.Text), Convert.ToSingle(SimpleNum2.Text));
                }
                catch(FormatException)
                {
                    SimpleResult.Text = "Please Enter Valid Numbers";
                }
            }
            else if (b.Name == "SimpleMinus") {
                SimpleCalc s = new SimpleCalc();
                try
                {
                    SimpleResult.Text = "Result: " + s.subtract(Convert.ToSingle(SimpleNum1.Text), Convert.ToSingle(SimpleNum2.Text));
                }
                catch (FormatException)
                {
                    SimpleResult.Text = "Please Enter Valid Numbers";
                }
            }
            else if (b.Name == "SimpleMultiply") {
                SimpleCalc s = new SimpleCalc();
                try
                {
                    SimpleResult.Text = "Result: " + s.multiply(Convert.ToSingle(SimpleNum1.Text), Convert.ToSingle(SimpleNum2.Text));
                }
                catch (FormatException)
                {
                    SimpleResult.Text = "Please Enter Valid Numbers";
                }
            }
            else if (b.Name == "SimpleDivide") {
                SimpleCalc s = new SimpleCalc();
                try
                {
                    SimpleResult.Text = "Result: " + s.divide(Convert.ToSingle(SimpleNum1.Text), Convert.ToSingle(SimpleNum2.Text));
                }
                catch (FormatException)
                {
                    SimpleResult.Text = "Please Enter Valid Numbers";
                }
            }
            else if (b.Name == "SimplePower")
            {
                SimpleCalc s = new SimpleCalc();
                try
                {
                    SimpleResult.Text = "Result: " + s.pow(Convert.ToSingle(SimpleNum1.Text), Convert.ToSingle(SimpleNum2.Text));
                }
                catch (FormatException)
                {
                    SimpleResult.Text = "Please Enter Valid Numbers";
                }
            }
            else if (b.Name == "SimpleModulous")
            {
                SimpleCalc s = new SimpleCalc();
                try
                {
                    SimpleResult.Text = "Result: " + s.mod(Convert.ToSingle(SimpleNum1.Text), Convert.ToSingle(SimpleNum2.Text));
                }
                catch (FormatException)
                {
                    SimpleResult.Text = "Please Enter Valid Numbers";
                }
            }
            else if (b.Name == "ComplexPlus") {
                ComplexCalc c = new ComplexCalc();
                try
                {
                   cFloat num1 = new cFloat(Convert.ToSingle(ComplexReal1.Text), Convert.ToSingle(ComplexImg1.Text));
                   cFloat num2 = new cFloat(Convert.ToSingle(ComplexReal2.Text), Convert.ToSingle(ComplexImg2.Text));
                    cFloat res = c.add(num1, num2);
                    ComplexResult.Text = "Result: (" + res.getReal() + "," + res.getImg() + ")";
                }
                catch (FormatException)
                {
                    ComplexResult.Text = "Please Enter Valid Numbers";
                }
            }
            else if (b.Name == "ComplexMinus") {
                ComplexCalc c = new ComplexCalc();
                try
                {
                    cFloat num1 = new cFloat(Convert.ToSingle(ComplexReal1.Text), Convert.ToSingle(ComplexImg1.Text));
                    cFloat num2 = new cFloat(Convert.ToSingle(ComplexReal2.Text), Convert.ToSingle(ComplexImg2.Text));
                    cFloat res = c.subtract(num1, num2);
                    ComplexResult.Text = "Result: (" + res.getReal() + "," + res.getImg() + ")";
                }
                catch (FormatException)
                {
                    ComplexResult.Text = "Please Enter Valid Numbers";
                }
            }
            else if (b.Name == "ComplexMultiply") {
                ComplexCalc c = new ComplexCalc();
                try
                {
                    cFloat num1 = new cFloat(Convert.ToSingle(ComplexReal1.Text), Convert.ToSingle(ComplexImg1.Text));
                    cFloat num2 = new cFloat(Convert.ToSingle(ComplexReal2.Text), Convert.ToSingle(ComplexImg2.Text));
                    cFloat res = c.multiply(num1, num2);
                    ComplexResult.Text = "Result: (" + res.getReal() + "," + res.getImg() + ")";
                }
                catch (FormatException)
                {
                    ComplexResult.Text = "Please Enter Valid Numbers";
                }
            }
            else if (b.Name == "ComplexDivide") {
                ComplexCalc c = new ComplexCalc();
                try
                {
                    cFloat num1 = new cFloat(Convert.ToSingle(ComplexReal1.Text), Convert.ToSingle(ComplexImg1.Text));
                    cFloat num2 = new cFloat(Convert.ToSingle(ComplexReal2.Text), Convert.ToSingle(ComplexImg2.Text));
                    cFloat res = c.divide(num1, num2);
                    ComplexResult.Text = "Result: (" + res.getReal() + "," + res.getImg() + ")";
                }
                catch (FormatException)
                {
                    ComplexResult.Text = "Please Enter Valid Numbers";
                }
            }
        }
    }
}
