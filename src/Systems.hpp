/**
 * @author      : mailitg (mailitg@$HOSTNAME)
 * @file        : Systems
 * @created     : Saturday Jan 04, 2025 20:52:04 CET
 */

#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP

#include "Components.hpp"
#include "ECS.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/mat4x4.hpp"

#include <unordered_map>
#include <vector>

class MeshSystem
{
    public:
        MeshSystem() = delete;
        ~MeshSystem();

        static void upload(std::vector<Entity> entities, void *args);
        static void draw(std::vector<Entity> entities, void *args);
        static void init(std::vector<Entity> entities, void *args);
        static void end(std::vector<Entity> entities, void *args);

    private:
};


class TextureSystem
{
    public:
        TextureSystem () = delete;
        ~TextureSystem();

        static void init(std::vector<Entity> entities, void *args);
        static GLuint get_texture_id();
        static int get_tile_size();
        static int get_tile_hor_count();

    private:
        static GLuint texture_id;
        static const std::string path;
        /* static std::unordered_map<std::string, std::pair<glm::vec2, glm::vec2>> texture_uv_map; */
        static std::pair<glm::vec2, glm::vec2> texture_uvs[];
        static int tile_size;
        static int tile_hor_count;
};


class PhysicSystem
{
    public:
        PhysicSystem() = delete;
        ~PhysicSystem();

        static void update(std::vector<Entity> entities, void *args);

    private:
};


class ControllerSystem
{
    public:
        ControllerSystem() = delete;
        ~ControllerSystem();

        static void process_input(std::vector<Entity> entities, void *args);

    private:
};

class CameraSystem {
    public:
        CameraSystem() = delete;
        ~CameraSystem();

        static void init(std::vector<Entity> entities, void* args);
        static void update_camera(std::vector<Entity> entities, void* args);

    private:
        static void create_projection_matrix(float screen_width, float screen_height, glm::mat4& proj_matrix);
        static void create_view_matrix(int screen_height, glm::mat4& view_matrix, Transform* transform);

};

class AnimateSystem
{
    public:
        AnimateSystem() = delete;
        ~AnimateSystem();

        static void animate(std::vector<Entity> entities, void *args);

    private:
};

#endif 

