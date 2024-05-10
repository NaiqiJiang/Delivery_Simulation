
# README

## Team-010-58
- Naiqi Jiang (JIAN0802)
- RuiRui Xu (Xu000705)
- Guolong Zhao (Zhao1736)
- JIAHAO Sun (Sun00647)

## Project Overview
In this project, we simulate drone-based package delivery using a detailed map of the University of Minnesota - Twin Cities. The simulation encompasses various navigational routes, tailored to illustrate realistic delivery scenarios. Central to this simulation are diverse drone models, each designed to cater to different delivery needs. A notable innovation in our model is the introduction of the "Dragon" entity, a conceptual equivalent to a delivery truck, which has the capacity to transport multiple packages simultaneously, thereby enhancing delivery efficiency. This approach mirrors real-world logistics where delivery vehicles often carry several packages in one trip. Additionally, we have integrated a battery feature into our drones, simulating the real-world constraint of limited battery life. This aspect of the simulation ensures that drones must periodically return to charging stations, adding a layer of complexity and realism to the model. This project aims not only to replicate the efficiency of real-life deliveries but also to incorporate the practical challenges faced in drone-based delivery systems.



## How to Run the Simulation
1. Navigate to the project folder and forward a port (default 8081).
2. Compile the code with `make -j` and run it using `make run`.
3. Access the simulation at `http://localhost:8081/`.
4. For scheduling deliveries, visit `http://127.0.0.1:8081/schedule.html`.
5. If you encounter a port conflict, change the port as needed (e.g., `./build/bin/transit_service 8082 apps/transit_service/web`).

## Simulation Details
Our simulation creates a dynamic environment by including a variety of entities such as helicopters, humans, ducks, drones, dragons, robots, and packages, each serving a specific purpose to enhance realism. While helicopters, humans, and ducks are included to mimic real-life scenarios without specific functionalities, robots and packages play a central role in the simulation. Robots act as customers, scheduling the delivery of packages, which represent the items being delivered. The core of our simulation lies in the efficient management of these package deliveries. We use a decorator pattern to assign varying weights to packages, allowing the delivery entities—drones for lighter packages and more powerful dragons for heavier or multiple packages—to handle them accordingly. This design choice closely aligns with real-world logistics, where delivery vehicles are tasked based on the nature and quantity of the cargo. To add interactivity and versatility, we have integrated 'random' and 'weight' buttons in the HTML interface; the former generates multiple packages for delivery, while the latter assigns weights to packages, impacting their distribution and delivery process. Furthermore, the introduction of a battery feature adds a layer of strategic planning and realism to the simulation, requiring drones to consider their battery capacity for consecutive deliveries. This combination of diverse entities and interactive features not only enriches the user experience but also enhances the practicality and authenticity of the simulation.



## New Features

### Feature 1: Delivering Multiple Packages
This feature revolutionizes our simulation by enabling the efficient delivery of multiple packages, a key aspect of real-world delivery systems. It introduces a powerful new entity, the "Dragon," designed for enhanced capacity and strength, making it ideal for transporting heavier packages. Accompanying this is a package weight decorator, which categorizes packages by weight, allowing for differentiated delivery methods: lighter packages (under 50 units) are assigned to drones, while heavier ones are managed by the Dragon. This addition not only brings a greater level of realism and practicality to the simulation but also expands its capabilities significantly. The use of Factory and Decorator design patterns simplifies code management, enhances flexibility, and promotes dynamic functionality and scalability in handling various package types. Users can experience this feature by specifying package weights in the simulation’s scheduling interface, directing the appropriate delivery entity based on the package's weight.

### Feature 2: Battery Management for Drones
The Battery Management feature introduces a critical layer of realism and strategic complexity to our drone delivery simulation. It equips drones with a battery management system that requires them to monitor their battery levels post-delivery. If sufficient battery remains, they proceed to the next delivery; otherwise, they autonomously navigate to a charging station for recharging. This feature not only mimics real-world drone operations where battery management is essential but also adds an element of strategic planning and optimization to the simulation. It enhances the existing framework by adding depth to the drone's decision-making process, making the simulation more challenging and authentic. The implementation of this feature utilizes the Decorator pattern, allowing for the dynamic addition of battery management to drones without altering their core functionalities. This approach maintains the separation of concerns and supports future extensions. Users can observe this feature in action as drones in the simulation autonomously manage their battery levels and make decisions about recharging during their delivery schedules.
### Instructions for New Features
- For Feature 1, enter the package weight in the scheduling form to determine the delivery entity (drone or Dragon).
- For Feature 2, drones with the battery decorator will manage their battery levels automatically during deliveries.

## Sprint Retrospective - Month 12

### Team Members
- Naiqi Jiang, Jiahao Sun: Worked on Weight Decorator and Multiple Package Delivery.
- Guolong Zhao, Ruirui Xu: Focused on the Battery Decorator.

### Achievements
- Successful implementation of the Weight and Battery Decorators.
- Effective team collaboration and problem-solving.

### Challenges
- Optimizing multiple package delivery logic.
- Implementing efficient battery management for drones.
- Time management for balancing various project components.

### Action Items
- Refining delivery and battery management features.
- Comprehensive Doxygen documentation by each team member.
- Improved time management strategies.

### Doxygen Documentation Responsibilities
- Naiqi Jiang, Jiahao Sun: Documenting Weight Decorator and Multiple Package Delivery.
- Guolong Zhao, Ruirui Xu: Documenting Battery Decorator.

# My Markdown Document

Here is the WeightDecorator and Dragon UML chart:
https://lucid.app/lucidchart/1fc1471e-6665-4bd4-8c38-2da96d22fb77/edit?viewport_loc=-56%2C-216%2C5251%2C2842%2C0_0&invitationId=inv_487f7c7d-0d3a-429d-b01b-5fa9167acf85

Here is the BatteryDecorator and Charger UML chart:
https://lucid.app/lucidchart/6adcbe43-d09f-4791-93b4-07a166251895/edit?viewport_loc=-1502%2C-1427%2C4403%2C2383%2C0_0&invitationId=inv_d981b043-5213-47ee-b118-054055a52581

YouTube Link:
https://www.youtube.com/watch?v=TQAKwaaUbSE&ab_channel=secretcontact

Docker Link:
https://hub.docker.com/repository/docker/guolongzhao/team-010-58-hw4/general

---

*End of README.md*
