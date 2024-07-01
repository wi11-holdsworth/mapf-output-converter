with open("test/test.csv", "r") as infile, open("test/test.csv.imp", "w") as outfile:
    lines: list[str] = infile.readlines()
    num_agents: int = lines[1].split(",")[3]

    outfile.write(lines[0])
    lines: list[str] = lines[1:]

    for i in range(1, int(num_agents) + 1):
        for j in range(i):
            if j == 0:
                line: list[str] = lines[0].split(",")
                line[3] = str(i)
                outfile.write(",".join(line))
                continue
            
            outfile.write(lines[j])
