# How to Add an Enemy

To add an enemy, follow these steps:

1. **Create Enemy Skin**:
   - First, create a skin for the enemy by creating a file in the `Json/Client/Entities` directory.

2. **Define Enemy Properties**:
   - Inside the file, define the enemy properties using a JSON format. For example, you can use the `basicEnemy.json` template.

   Example `basicEnemy.json`:
   ```json
   {
    "name": "BasicEnemy",
    "transform": {
        "scale": {
            "x": 1,
            "y": 1
        }
    },
    "plugins": [
        {
            "name": "PrintablePlugin",
            "type": "sprite",
            "texture": {
                "path": "./Assets/Enemy/basicEnemy.gif"
            },
            "zIndex": -1,
            "textureRect": {
                "x": 0,
                "y": 0,
                "width": 32,
                "height": 32
            }
        },
        {
            "name": "PhysicsPlugin",
            "isOverlap": true,
            "boxes": []
        },
        {
            "name": "Animation",
            "animations": [
                {
                    "name": "idle",
                    "time": 0.1,
                    "frames": [
                        {
                            "x": 224,
                            "y": 0,
                            "width": 32,
                            "height": 32
                        }
                    ]
                }
            ]
        }

    ],
    "children": []
   }
   ```


   ## Explanation of Parameters:

   - `name`: The name of the entity, in this case, "BasicEnemy".

   - `transform`: Describes the transformation properties of the entity.

     - `scale`: Specifies the scaling factors along the x and y axes. In this case, the entity has a scale of 1 in both dimensions.

   - `plugins`: Contains an array of plugins that define additional functionality for the entity.

     - `PrintablePlugin`: Renders the entity as a sprite.

       - `type`: Specifies that the printable plugin renders a sprite.

       - `texture`: Defines the properties of the texture used for the sprite.

         - `path`: The file path to the texture image.

       - `zIndex`: Sets the render depth of the sprite.

       - `textureRect`: Specifies the portion of the texture to be used.

     - `PhysicsPlugin`: Manages the physics properties of the entity.

       - `isOverlap`: Indicates if the entity can overlap with other objects.

       - `boxes`: An array of bounding boxes used for collision detection. (Currently empty in this example)

     - `Animation`: Enables animation for the entity.

       - `animations`: Contains an array of animation sequences.

         - `name`: The name of the animation sequence, in this case, "idle".

         - `time`: The time in seconds between each frame.

         - `frames`: Contains an array of frames that make up the animation.

           - `x`: The x-coordinate of the frame in the texture.

           - `y`: The y-coordinate of the frame in the texture.

           - `width`: The width of the frame.

           - `height`: The height of the frame.

   - `children`: An array that can hold child entities. In this case, it's empty.
  
   ***Initialize in Test Scene***:
      - Initialize the enemy in the Json/Client/Scene/test.json file by adding it to the list of entities.

   ***Create Server-Side Enemy***:
      - Create a file for the enemy on the server side in the Json/Server/Scene/Enemies directory, following a similar process as above.


   Example `basicEnemy.json`:
   ```json
   {
    "random": 10,
    "name": "Tank",
    "plugins": [
        {
            "name": "Entity",
            "speed": 100,
            "hp": 300,
            "type": "enemy",
            "ai": false,
            "spawnProjectile": {
                "x": 0,
                "y": 0
            },
            "attacks": [
                {
                    "damage": 15,
                    "cooldown": 2,
                    "projectile": "./Json/Server/Scene/Projectile/BasicProjectile.json"
                },
                {
                    "damage": 40,
                    "cooldown": 10,
                    "projectile": "./Json/Server/Scene/Projectile/BigProjectile.json"
                }
            ]
        },
        {
            "name": "PhysicsPlugin",
            "isOverlap": true,
            "boxes": [{
                "x": 0,
                "y": 0,
                "width": 51,
                "height": 59
            }]
        }
    ]
   }
   ```

   ## Explanation of Parameters:

   - `random`: A numerical value set to 10.

   - `name`: The name of the entity, which is "Tank".

   - `plugins`: An array containing two plugin objects that define additional functionality for the entity.

     - `Entity`: Specifies properties related to the entity itself.

       - `speed`: The speed of the entity, set to 100.

       - `hp`: The health points (hit points) of the entity, set to 300.

       - `type`: The type of the entity, in this case, "enemy".

       - `ai`: A boolean value indicating whether the entity has artificial intelligence (AI), set to `false`.

       - `spawnProjectile`: The position (x, y) at which projectiles are spawned from the entity, initially set to (0, 0).

       - `attacks`: An array containing multiple attack configurations.

         - `damage`: The damage dealt by an attack, which can vary.

         - `cooldown`: The cooldown time between attacks, measured in seconds.

         - `projectile`: The JSON file that defines the projectile used in the attack.

     - `PhysicsPlugin`: Manages the physics properties of the entity.

       - `isOverlap`: Indicates whether the entity can overlap with other objects, set to `true`.

       - `boxes`: An array of bounding boxes used for collision detection. In this case, there is one box defined with specific dimensions (x, y, width, and height).
  
   ***Initialize in Main Server Scene***:
      - Initialize the enemy in the Json/Server/Scene/mainScene.json file on the server side.
  
   ### Now, you have successfully added an enemy to your game!
