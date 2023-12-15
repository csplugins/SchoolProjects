package mainFraction;

import java.util.Scanner;
/**This class will loop and get input for two fractions and an operation
 * to perform on them. The operation will have a new final fraction
 * that can be reduced 
 *
 * @author Cody Skala (cws26)
 * @version 1.0 Build 1 Sept 21, 2015.
 */
public class MainFraction {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int a, b, c, d;
        char operation;
        do{
        System.out.println("Enter the Numerator of the first fraction");
        a = in.nextInt();
        System.out.println("Enter the Denominator of the first fraction");
        b = in.nextInt();
        Fraction fraction1 = new Fraction(a, b);
        System.out.println("Enter the operation to perform (+ - * / =)");
        operation = in.next().charAt(0);
        while(operation != '+' && operation != '-' && 
                operation != '*' && operation != '/' && operation != '='){
            System.out.println("Not a valid operator, please select "
                    + "+ to add, - to subtract, * to multiply, "
                    + "/ to divide, or = to check for equality.");
            operation = in.next().charAt(0);
        }
        System.out.println("Enter the Numerator of the second fraction");
        c = in.nextInt();
        System.out.println("Enter the Denominator of the second fraction");
        d = in.nextInt();
        Fraction fraction2 = new Fraction(c, d);
        System.out.println("\nCalculating " + a + "/" + b + " " + operation
            + " " + c + "/" + d);
        if(operation == '+')
            fraction1.add(fraction2);
        else if(operation == '-')
            fraction1.subtract(fraction2);
        else if(operation == '*')
            fraction1.multiply(fraction2);
        else if(operation == '/')
            fraction1.divide(fraction2);
        else{
            if(fraction1.equals(fraction2))
                System.out.println("They are equal!");
            else
                System.out.println("They are not equal.");
            System.out.println(fraction2);
        }
        System.out.println(fraction1);
        System.out.println("Enter Y to go again. Anything else to exit");
        operation = in.next().charAt(0);
        }while(operation == 'y' || operation == 'Y');
    }
}