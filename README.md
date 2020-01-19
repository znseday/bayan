# bayan
hw_09 for OTUS

The task description is in 'Task_bayan.pdf'

## Parameters:

```bash
-h, --help			Show help
-H, --hash			Hash type: SHA1, crc32
-b, --blocksize	Block size (in bytes), default value = 64
-f, --files			files to check
```

**Examples**: 

`bayan --hash sha1 --blocksize 128 1.txt 2.txt 3.txt`
`bayan -h crc32 1.txt 2.txt 3.txt`
