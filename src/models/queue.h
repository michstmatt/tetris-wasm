#include "blocks.h"
#define QUEUE_LEN 4
typedef struct
{
    Block Blocks[QUEUE_LEN];
    int Index;
    int Length;
} BlockQueue;

Block QueuePopPush(BlockQueue *queue)
{
    Block block = queue->Blocks[queue->Index];
    Block *ptr = (Block *)(&queue->Blocks[queue->Index]);
    randBlock(ptr);
    queue->Index++;
    if (queue->Index >= queue->Length)
    {
        queue->Index = 0;
    }
    return block;
}

void SeedQueue(BlockQueue *queue)
{
    for (int i = 0; i < queue->Length; i++)
    {
        Block *ptr = (Block *)(&queue->Blocks[i]);
        randBlock(ptr);
    }
}
