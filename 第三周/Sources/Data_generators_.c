#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_data(int count, const char *filename)
{
    // 打开文件
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        perror("fopen failed");
        return; // 不强制退出程序，交由调用者处理错误
    }

    // 设置随机数种子（仅需设置一次）
    static int seed_set = 0;
    if (!seed_set)
    {
        srand((unsigned)time(NULL));
        seed_set = 1;
    }

    // 缓冲区用于批量写入，提升性能
    const int buffer_size = 1024;
    char buffer[buffer_size];
    int buffer_index = 0;

    for (int i = 0; i < count; i++)
    {
        int x = rand() % 100; // 正确生成随机数 [0, 99]
        int len = snprintf(buffer + buffer_index, buffer_size - buffer_index, "%d\n", x);
        buffer_index += len;

        // 如果缓冲区接近满，写入文件并清空缓冲区
        if (buffer_index >= buffer_size - 100) // 留出足够空间避免溢出
        {
            fwrite(buffer, 1, buffer_index, file);
            buffer_index = 0;
        }
    }

    // 写入剩余数据
    if (buffer_index > 0)
    {
        fwrite(buffer, 1, buffer_index, file);
    }

    // 关闭文件并检查是否成功
    if (fclose(file) != 0)
    {
        perror("fclose failed");
    }

    printf("Generate %d data to %s\n", count, filename);
}

int main()
{
    printf("Ready to generate data...\n");
    printf("Please input the number of data:");
    int n;
    scanf("%d", &n);
    generate_data(n, "Data.txt");
    return 0;
}