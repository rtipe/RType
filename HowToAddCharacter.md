# Adding a Character to Your C++ Project

## Creating the Enemy's Skin

To add an enemy to your project, you first need to create its appearance, known as the "skin." Follow these steps:

1. Create a file in the `Json/Client/Entities` directory to represent your enemy.

2. Inside the file, describe the enemy's properties using JSON format.

   Here's a basic example of the `basicEnemy.json` file:

   ```json
   {
       "name": "Basic Enemy",
       "health": 100,
       "damage": 10,
       "speed": 2.0,
       "sprite": "basic_enemy.png"
   }

   You can customize the properties based on your game.

## Initializing the Enemy in the Client Scene File

Once you have created the JSON file for the enemy, you need to initialize it in your client scene file:

1. Open the `Json/Client/Scene/test.json` file.

2. Inside this file, add the enemy's reference as follows:

```json
"entities": [
    {
        "type": "character",
        "skin": "Entities/basicEnemy.json",
        "position": {
            "x": 100,
            "y": 200
        }
    }
]
```
## Creating the Server-Side Character File

To synchronize the character with the server, you need to create a server-side character file. Follow the same pattern as before:

1. Create a file in the `Json/Server/Scene/Character` directory to represent your character on the server.

2. Inside the file, describe the character's properties using JSON format.

   Customize the properties to match your game's requirements.

## Initializing the Server-Side Character in the Main Server Scene

Now, initialize the character on the server in the main scene file:

1. Open the `Json/Server/Scene/mainScene.json` file.

2. Inside this file, add the character's reference in the server scene:

   ```json
   "characters": [
       {
           "type": "character",
           "character_file": "Character/yourCharacterFile.json"
       }