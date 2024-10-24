// const validityCheck = /[^ACDEFGHIKLMNPQRSTVWY]/;

const full_file = await Bun.file("raw_data.csv").text();
const formatted_data: { classification: string; sequence: string }[] = full_file.split("\r\n").map((x) => {
    const elements = x.split(",");
    return {
        classification: elements[1],
        sequence: elements[0],
    };
});

const lineate = (str: string): string => {
    return str.match(/\w{1,80}/g)?.join("\n") ?? "";
};

let output = "";

for (let i = 0; i < formatted_data.length; i++) {
    // if (formatted_data[i].sequence.match(validityCheck) === null) continue;
    output += `> ${i + 1} | ${formatted_data[i].classification}\n`;
    output += lineate(formatted_data[i].sequence);
    if (i !== formatted_data.length - 1) {
        output += "\n";
    }
}

Bun.write("training_data.fasta", output);
