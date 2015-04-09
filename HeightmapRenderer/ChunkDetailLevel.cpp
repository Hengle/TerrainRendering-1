#include "Commons.h"
#include "ChunkDetailLevel.h"

void ChunkDetailLevel::generateDetailLevels(int meshSize, int chunkSize)
{
    this->meshSize = meshSize;
    this->chunkSize = chunkSize;
    restartIndexToken = meshSize * meshSize;

    for(int lodLevel = 0; lodLevel < 3; lodLevel++)
    {
        int nextSize = (chunkSize - 1) / std::pow(2, lodLevel) + 1;
        int stepMultiplier = std::pow(2, lodLevel);

        for(int i = 0; i < nextSize - 1; i++)
        {
            for(int j = 0; j < nextSize; j++)
            {
                indicesLoD[lodLevel].push_back(
                    ((i + 1) * chunkSize + j) * stepMultiplier
                );
                indicesLoD[lodLevel].push_back(
                    (i * chunkSize + j) * stepMultiplier
                );
            }

            indicesLoD[lodLevel].push_back(restartIndexToken);
        }
    }

    indicesCombinationGenerated = true;
}

void ChunkDetailLevel::bindBufferData()
{
    for(int lodLevel = 0; lodLevel < 3; lodLevel++)
    {
        indicesBuffer[lodLevel].Bind(Buffer::Target::ElementArray);
        {
            Buffer::Data(Buffer::Target::ElementArray, indicesLoD[lodLevel]);
        }
        indexSizes[lodLevel] = indicesLoD[lodLevel].size();
        // we don't need the indices once uploaded to gpu
        indicesLoD[lodLevel].clear();
    }

    gl.Enable(Capability::PrimitiveRestart);
    gl.PrimitiveRestartIndex(restartIndexToken);
}

void ChunkDetailLevel::bindBuffer(int levelOfDetail)
{
    levelOfDetail = std::min(std::max(0, levelOfDetail), 2);
    indicesBuffer[levelOfDetail].Bind(Buffer::Target::ElementArray);
}

int ChunkDetailLevel::indicesSize(int levelOfDetail)
{
    levelOfDetail = std::min(std::max(0, levelOfDetail), 2);
    return indexSizes[levelOfDetail];
}

ChunkDetailLevel::ChunkDetailLevel()
{
}

ChunkDetailLevel::~ChunkDetailLevel()
{
}
