const full_file = await Bun.file("raw_data.csv").text();

const amino_acid_letters = "ACDEFGHIKLMNPQRSTUVWXYZ";
const possible_pairs = amino_acid_letters
    .split("")
    .map((x) => {
        return amino_acid_letters.split("").map((y) => {
            return `${x}${y}`;
        });
    })
    .flat();

const analysis_template: { [key: string]: number } = {};
for (const pair of possible_pairs) {
    analysis_template[pair] = 0;
}

const data = full_file.split("\r\n").map((x) => {
    const elements = x.split(",");
    const analysis = Object.assign({}, analysis_template);

    for (let i = 0; i < elements[0].length - 1; i++) {
        const pair = elements[0].substring(i, i + 2);
        analysis[pair]++;
    }

    return {
        full_sequence: elements[0],
        classification: elements[1],
        analysis,
    };
});

function recursive_join(arr: any[], joiner: string): string {
    let toReturn = "";
    for (const x of arr) {
        if (typeof x !== "object") {
            toReturn += x + joiner;
        } else {
            toReturn += recursive_join(Object.values(x), joiner);
        }
    }
    return toReturn;
}

let toPrint: string = `sequence,classification,${possible_pairs.join(",")}\n`;
for (const x of data) {
    toPrint += recursive_join(Object.values(x), ",") + "\n";
}

Bun.write("frequency_analysis.csv", toPrint);
// Bun.write("temp.json", JSON.stringify(data, null, 4));
