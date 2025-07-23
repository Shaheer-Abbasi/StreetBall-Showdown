# StreetBall-Showdown

A C++ basketball-themed tournament game where you face AI opponents in 5 matches to win the championship!

## Game Concept
- Tournament-style gameplay where you must win 5 matches in a row
- Each match consists of 20 turns - highest score wins
- Three unique player classes with different abilities
- Save/Load functionality to continue your progress

## Player Classes

### 🏀 Shooter 
- High stamina
- Lower base accuracy
- "In the zone" mechanic - successful shots increase future accuracy

### 💪 Slasher 
- Lower stamina
- Higher base accuracy
- "And-one" chance - possibility for bonus points

### � Specialist 
- Highest base accuracy
- "Ankle breaker" chance - creates highly accurate shot opportunities

## Features
- Random number generation for shot probability
- Announcer-style commentary during matches
- Character progression system (XP and levels)
- Save/Load functionality via text files
- Simple AI opponents with random decision-making

## How to Play
1. Choose to create a new character or load an existing one
2. Select your player class (Shooter, Slasher, or Specialist)
3. Play through 5 matches against AI opponents
4. Win all 5 to claim the championship!
5. Save your character between matches if desired

## Development Notes
- Built using C++ with OOP principles
- Abstract base class with three derived classes
- Random shot probability handled via custom `Rand.h` class
