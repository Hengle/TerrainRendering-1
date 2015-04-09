#pragma once
using namespace oglplus;

class ChunkDetailLevel
{
    private:
        // chunk params
        int meshSize;
        int chunkSize;
    private:
        // triangle strip primitive restart at
        int restartIndexToken;
        // base indices configuration for 3 levels of detail
        // vectors are cleared once data is uploaded to GPU
        std::array<std::vector<unsigned int>, 3> indicesLoD;
    private:
        Context gl;
        // indices count on level of detail
        std::array<int, 3> indexSizes;
        // avoid creating indices again if mesh has the same configuration
        bool indicesCombinationGenerated;
        // indices combinations for different lod levels
        std::array<Buffer, 3> indicesBuffer;
    public:
        // uploads index data to gpu
        void bindBufferData();
        // binds the indices based on lod
        void bindBuffer(int levelOfDetail);
        // indices count on level of detail
        int indicesSize(int levelOfDetail);
        // generates the 3 LoD indices configurations based on mesh and chunk size
        void generateDetailLevels(int meshSize, int chunkSize);
        // token to restart the triangle strip
        int RestartIndexToken() const { return restartIndexToken; }
        // indexes combinations per lod
        const std::array<std::vector<unsigned int>, 3> &IndicesLoD() { return indicesLoD; }

        ChunkDetailLevel();
        ~ChunkDetailLevel();
        // chunks size
        int ChunkSize() const { return chunkSize; }
        int MeshSize() const { return meshSize; }
};

