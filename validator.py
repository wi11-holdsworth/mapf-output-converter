with open("test.csv", "r") as fp:
    file = fp.readlines()
    record = file[1]
    moves = record.split(",")[6]
    actions = moves.split(";")

    ag = [""] * 950

    for action in actions:
        num, mv = action.split(":")
        if int(num) == 557:
            print("hi")
        ag[int(num)] += mv.rstrip("\n")

    with open("pyout", "w") as outfile:
        for mv in ag:
            outfile.write(mv + "\n")

