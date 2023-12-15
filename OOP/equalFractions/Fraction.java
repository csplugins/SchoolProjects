package cws26project2;

/**The Fraction class to handle the fraction operation. It can test for
 * addition, subtraction, multiplication, division, and if the two fractions are
 * equal. It will also throw an error if a denominator is ever zero.
 * 
 * @author Cody Skala
 * @version 1.0 Build 1 Sept 21, 2015.
 */
public class Fraction{
    private int num, den;
    /**This is the Fraction constructor with 2 parameters
     * @param a the numerator of the first fraction
     * @param b the denominator of the second fraction
     */
    public Fraction(int a, int b){
        if(b == 0)
            throw new ArithmeticException("One of the denominators was zero!");
        num = a;
        den = b;
    }
    /**The gcd method will find the greatest common denominator for a fraction
     * 
     * @param numerator the top number of a fraction
     * @param denominator the bottom number of a fraction
     * @return returns the greatest common denominator
     */
    private static int gcd(int numerator, int denominator){
        int temp;
        while(numerator != 0 && denominator != 0){
            temp = denominator;
            denominator = numerator % denominator;
            numerator = temp;
        }
        return numerator + denominator;
    }
    /**The add() takes 2 fractions and adds them to make one fraction
     * @param f2 the second fraction to be added to the first fraction
     */
    public void add(Fraction f2){
        this.num = this.num * f2.den + den * f2.num;
        this.den = this.den * f2.den;
        System.out.println("The fraction is " + this.num + "/" + this.den);
    }
    /**The subtract() takes 2 fractions and subtracts them to make one fraction
     * @param f2 the second fraction to be subtracted to the first fraction
     */
    public void subtract(Fraction f2){
        this.num = this.num * f2.den - den * f2.num;
        this.den = this.den * f2.den;
        System.out.println("The fraction is " + this.num + "/" + this.den);
    }
    /**The multiply() takes 2 fractions and multiplies them to make one fraction
     * @param f2 the second fraction to be multiplied to the first fraction
     */
    public void multiply(Fraction f2){
        this.num = this.num * f2.num;
        this.den = this.den * f2.den;
        System.out.println("The fraction is " + this.num + "/" + this.den);
    }
    /**The divide() takes 2 fractions and divides them to make one fraction
     * @param f2 the second fraction to be divided to the first fraction
     */
    public void divide(Fraction f2){
        if(f2.num == 0 || f2.den == 0)
            throw new ArithmeticException("The second fraction caused division of zero!\n"
                    + "Cannot divide by zero!");
        this.num = this.num * f2.den;
        this.den = this.den * f2.num;
        System.out.println("The fraction is " + this.num + "/" + this.den);
    }
    /**The equals() takes 2 fractions and compares their floating values
     * @param obj the object that is passed to check if it is equal to 'this'
     * @return Returns true or false based on the comparison result
     */
    @Override
    public boolean equals(Object obj) {
        if (obj == this) {
            return true;
        }
        if (!(obj instanceof Fraction)) {
            return false;
        }
        Fraction temp = (Fraction) obj;
        double comp1 = (double)this.num/this.den;
        double comp2 = (double)temp.num/temp.den;
        return Double.compare(comp1, comp2) == 0;
    }
    /**The hashCode is needed for testing equality with a similar hash code
     * 
     * @return The hash is returned and compared to another hash for equality
     */
    @Override
    public int hashCode() {
        int hash = 7;
        hash = 71 * hash + this.num;
        hash = 71 * hash + this.den;
        return hash;
    }
    /**The toString() has something printed to console replacing its default
     * 
     * @return Returns a new string to be used inside of System.out.println()
     */
    @Override
    public String toString() {
        int temp1, temp2, gcd;
        gcd = Fraction.gcd(this.num, this.den);
        temp1 = this.num / gcd;
        temp2 = this.den / gcd;
        if (temp2 == 1)
            return this.num + "/" + this.den + " reduced is " + temp1;
        return this.num + "/" + this.den + " reduced is " + temp1 + "/" + temp2;
    }
}
