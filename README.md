# TowerDefense-Qt  
**2020 "Programming II" Final Project**  
— Tower Defense Game  

## 1. Objective  
The goal of this project is to develop a tower defense game, allowing students to gain an in-depth understanding of various object-oriented (OO) development principles and concepts. Through this process, students will build a comprehensive knowledge of C++ development while also cultivating skills in project management and product development.  

## 2. Introduction to Tower Defense Games  
Tower defense games are a subgenre of real-time strategy games in which players construct defensive towers (or similar structures) on a map to prevent enemies from reaching a designated stronghold.  

Typically, enemies do not actively attack the towers. When an enemy is eliminated, the player earns points or rewards, which can be used to purchase or upgrade towers. Enemies attack in waves, and most tower defense games provide a pause between waves, allowing players to upgrade or add towers using accumulated points.  

A typical game consists of around **50 or more waves**. Players usually have a **limited number of lives**; if an enemy reaches the designated endpoint, the player's lives will decrease. As the player upgrades their towers, the number and strength of enemies also increase. Generally, **enemy progression outpaces the rate of tower upgrades**.  

The primary goal of such games is to **survive for a specified duration or as long as possible**.  

## 3. Functional Requirements  
The project requires the development of a **complete tower defense game**, implementing both **fundamental** and **enhanced** gameplay features.  

### (1) Basic Features  
- Multiple enemy types and diverse attack methods.  
- Various types of defensive towers, each with distinct attributes.  
- Increasing game difficulty as the game progresses.  
- Background music and event sound effects (optional).  

### (2) Enhanced Features  
- Tower upgrade functionality.  
- Basic AI for enemy attacks.  
- Accumulation of player resources (points) to enable tower upgrades.  
- Ability to dismantle defensive towers.  
- Multiple game scenes and level-switching mechanics.  

## 4. Object-Oriented (OO) Design Principles  
The game design should effectively demonstrate key OO principles:  

1. **Encapsulation** – Use of classes, overloaded constructors, etc.  
2. **Inheritance** – For example, a hierarchical structure such as:  
   - `Object → Enemy → Attacking Enemy`  
   - `Object → Defense Tower → Slow-Firing Defense Tower`  
3. **Polymorphism** – Abstract base classes with derived classes implementing various UI elements.  
4. **Composition** – For instance, the **Defense Tower** class containing a **Weapon** class.  
5. **Const-Correctness** – Use of `const` member functions and objects, such as in the **Weapon** class.  

This project aims to integrate these OO features while delivering a **functional and engaging** tower defense game.
