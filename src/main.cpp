/**
 * @author      : mailitg (mailitg@$HOSTNAME)
 * @file        : main
 * @created     : Saturday Dec 28, 2024 13:39:02 CET
 */

#include "Components.hpp"
#include "ECS.hpp"
#include "Systems.hpp"
#include "glm/detail/qualifier.hpp"
#include "render/Renderer.hpp"

#include <iostream>
#include <vector>

#define GLEW_STATIC

int main()
{
    //initialize entitiesScene menu = ECS::create_scene();
    Scene menu = ECS:: create_scene();
    /* Scene niv1 = ECS:: create_scene(); */
    /* Scene niv2 = ECS::create_scene(); */
    /* Scene niv3 = ECS::create_scene(); */
    /* Scene niv4 = ECS::create_scene(); */
    /* Scene pause = ECS::create_scene(); */
    
    ECS::select_scene(menu);

    Entity player = ECS::create_entity();

    Entity path1 = ECS::create_entity();
    Entity path2 = ECS::create_entity();
    Entity path3 = ECS::create_entity();
    Entity path4 = ECS::create_entity();
    Entity path5 = ECS::create_entity();
    Entity path6 = ECS::create_entity();

    Entity lev1 = ECS::create_entity();
    Entity lev2 = ECS::create_entity();
    Entity lev3 = ECS::create_entity();
    Entity lev4 = ECS::create_entity();
    Entity lev5 = ECS::create_entity();
    Entity lev6 = ECS::create_entity();

    ECS::register_component<Transform>(); 
    ECS::register_component<Rigidbody>(); 
    ECS::register_component<Mesh>(); 
    ECS::register_component<Texture>(); 
    ECS::register_component<Controller>();
    ECS::register_component<Camera>();
    ECS::register_component<Animation>();

    std::string texture_path = "./src/render/textures/texture.jpg";

    ECS::add_component<Transform>(player, { .x=0, .y=0, .z=0 , .scale = glm::vec3(100, 100, 0)});
    ECS::add_component<Rigidbody>(player, { .mass = 1.0f , .velocity = {0.0f, 0.0f, 0.0f}}); 
    ECS::add_component<Controller>(player, { .speed = 200.0});
    ECS::add_component<Mesh>(player);
    ECS::add_component<Texture>(player, { .id=0 });

    ECS::add_component<Camera>(player, {
            .position=glm::vec3(0.0f, 0.0f, 5.0f),  
            .target=glm::vec3(0.0f, 0.0f, 0.0f),    
            .offset=glm::vec3(0.0f, 2.0f, 5.0f),    
            .smoothing_factor=0.1f                  
            });

    ECS::add_component<Animation>(player, {
            .current_frame=0,
            .frame_duration=0.08, 
            .frames=std::vector<int> {0, 1, 2, 3, 4, 5, 6, 7, 8, 79, 80},
            .mode=AnimationMode::OnInput
            });

    ECS::add_component<Transform>(path1, { .x=0, .y=0, .z=0, .scale = glm::vec3(100, 100, 0) });
    ECS::add_component<Mesh>(path1);
    ECS::add_component<Texture>(path1, { .id=18 });
    ECS::add_component<Animation>(path1, {.mode=AnimationMode::None});

    ECS::add_component<Transform>(path2, { .x=0, .y=0, .z=0, .scale = glm::vec3(100, 100, 0) });
    ECS::add_component<Mesh>(path2);
    ECS::add_component<Texture>(path2, { .id=18 });
    ECS::add_component<Animation>(path2, {.mode=AnimationMode::None});

    ECS::add_component<Transform>(path3, { .x=0, .y=0, .z=0, .scale = glm::vec3(100, 100, 0) });
    ECS::add_component<Mesh>(path3);
    ECS::add_component<Texture>(path3, { .id=18 });
    ECS::add_component<Animation>(path3, {.mode=AnimationMode::None});



    ComponentMask signature = ECS::create_signature<Mesh>();
    ECS::register_system(MeshSystem::init, signature, nullptr);

    signature = ECS::create_signature<Mesh>();
    ECS::register_system(MeshSystem::draw, signature, nullptr);

    signature = ECS::create_signature<Mesh, Transform, Texture, Animation>();
    ECS::register_system(MeshSystem::upload, signature, nullptr);

    ECS::register_system(TextureSystem::init, signature, nullptr);

    float delta_time = 0.0f;
    signature = ECS::create_signature<Rigidbody, Transform>();
    ECS::register_system(PhysicSystem::update, signature, &delta_time);

    signature = ECS::create_signature<Camera, Transform>();
    ECS::register_system(CameraSystem::init, signature, nullptr);
    ECS::register_system(CameraSystem::update, signature, &delta_time);

    signature = ECS::create_signature<Animation, Controller>();
    ECS::register_system(AnimationSystem::animate, signature, &delta_time);

    //initialize window
    Renderer::init();

    signature = ECS::create_signature<Controller>();
    ECS::register_system(ControllerSystem::process_input, signature, Renderer::window);

    //load textures and mesh
    ECS::call_system(MeshSystem::init);
    ECS::call_system(TextureSystem::init);
    ECS::call_system(CameraSystem::init);

    float previous_time = glfwGetTime();
    //game loop
    while(!glfwWindowShouldClose(Renderer::window))
    {
        float current_time = glfwGetTime();
        delta_time = current_time - previous_time;
        previous_time = current_time;

        Renderer::processInput(Renderer::window);
        ECS::call_system(ControllerSystem::process_input);

        glClearColor(1., 1., 1., 1.);
        glClear(GL_COLOR_BUFFER_BIT);  

        glUseProgram(Shader::program_id);
        ECS::call_system(PhysicSystem::update);
        ECS::call_system(CameraSystem::update);
        ECS::call_system(MeshSystem::upload);
        ECS::call_system(MeshSystem::draw);
        ECS::call_system(AnimationSystem::animate);

        glfwSwapBuffers(Renderer::window);
        glfwPollEvents(); 

    }

    ECS::call_system(MeshSystem::end);
    Shader::end();
    return 0;
}

