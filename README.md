# Evil Hangman - How to Play & Game Mechanic

## Game Mechanic

Evil Hangman is a tricky version of the classic hangman game that tries to avoid letting you guess the word easily. Instead of choosing one word at the start, it keeps a large pool of possible words and dynamically narrows it down based on your guesses — always picking the group of words that makes it hardest for you to find the letters.

Each time you guess a letter:
- The game groups remaining words by their pattern of that letter’s positions.
- It then chooses the largest group, often avoiding revealing letters if possible.
- This way, the hidden word "changes" behind the scenes to make you guess more!

You have 6 lives. Each wrong guess reduces a life and draws more of the hangman figure. The goal is to guess all letters before running out of lives.

---

## How to Play

1. When the game starts, it tells you how many letters are in the hidden word.
2. Type a letter guess and press Enter.
3. If the letter is in the word, it will be revealed in the correct positions.
4. If the letter is not in the word, you lose a life and the hangman figure updates.
5. Keep guessing letters until:
   - You reveal the whole word (you win), or
   - You run out of lives (game over).

---

Good luck, and beware — this hangman is truly evil! 😈
