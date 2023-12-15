using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization;

namespace RockPaperScissors
{
    /* This is the class for the AI that will play the rock paper scissors game.
   * The way that the AI will work is that it will have an array with the integer
   *  values between 0 and 2.
   *  
   *  0: represents rock
   *  1: represents paper
   *  2: represents scissors
   *  
   *  When a user clicks a button to select either rock paper or scissors the AI
   *  will then randomly select an index from the array and play whatever is in the 
   *  index. If the AI loses then it will replace the number in the cell with the
   *  number that would have won that round.
   *  
   *  The idea is that there will be a move that is played more often than the rest
   *  and most of the array spots will get filled with the winning moves. To achieve
   *  this the array will be serializeable to keep track of the previous learning.
   * 
   */
    [DataContract()] //this is used for serializable.
    public class RockPaperScissorsAI
    {
        [DataMember]
        private int[] moves;
        private const int rock = 0;
        private const int paper = 1;
        private const int scissors = 2;

        public RockPaperScissorsAI()
        {
            // Intially fill the array the first time
            // that the object is created.
            moves = fill_array();
        }

        private int[] fill_array()
        {
            Random rand = new Random();

            int[] temp = new int[100];
            for (int i = 0; i < 100; ++i)
            {
                temp[i] = rand.Next(0, 3);
            }

            return temp;
        }


        /* This function will chose the AI's move. It takes the move of the player
         * as the input. 
         * 
         * If the player wins the function will return the integer value '0'. 
         * 
         * If the AI wins then the function will return the integer value '1'.
         * 
         * If there is a tie then the function will return the integer value '2'.
         * 
         * When the AI loses then then this function will update the cell in the the
         * member variable choice array with the winning move. 
         * 
         * In the event of a tie the function will do nothing other that output there
         * is a tie.
         *  
         * Returns -1 in the event of an error
         */

        public int choose(int player_move)
        {
            Random rand = new Random();
            int cell = rand.Next(0, 3);
            int ai_move = moves[cell];

            if ((ai_move == rock && player_move == scissors) ||
                (ai_move == paper && player_move == rock) ||
                (ai_move == scissors && player_move == paper))
            {
                return 1;
            }
            else if ((ai_move == rock && player_move == paper) ||
                (ai_move == paper && player_move == scissors) ||
                (ai_move == scissors && player_move == rock))
            {
                update_moves(cell, player_move);
                return 0;
            }
            else if (ai_move == player_move)
            {
                return 2;
            }

            return -1;

        }

        /*
         * This function will update the cell in the choice array to set
         * the cell to the winning move.
         */

        private void update_moves(int cell, int player_move)
        {
            switch(player_move)
            {
                case rock:
                    moves[cell] = paper;
                    break;
                case paper:
                    moves[cell] = scissors;
                    break;
                case scissors:
                    moves[cell] = rock;
                    break;
            }

        }
    }
}
