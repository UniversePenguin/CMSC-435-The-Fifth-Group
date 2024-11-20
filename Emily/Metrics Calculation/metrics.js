let testData = `ConfusionMatrix:
True:    nonDRNA    RNA    DNA    DRNA
nonDRNA:    5368    23    8    0
RNA:    887    419    66    0
DNA:    1268    70    310    1
DRNA:    336    11    7    21`;

function findMetrics(input) {
    let splitData = input
        .split(/\n|\r\n/)
        .map((x) => x.split(/\t|    /))
        .filter((x) => x.length === 5)
        .map((x) => x.map((y) => (isNaN(parseInt(y)) ? y : parseInt(y))))
        .slice(0, 5);

    console.log(splitData);

    const labels = splitData.shift().splice(1);
    const rowLabels = splitData.map((x) => x.shift());

    const totalSamples = splitData.flat().reduce((a, b) => a + b);

    const categorizedData = {};

    labels.forEach((label, i) => {
        const regex = new RegExp(`\\b${label}`, "i");
        const relevantColumn = splitData.map((x) => x[i]);
        const relevantRowIndex = rowLabels.findIndex((x) => regex.test(x));

        if (relevantRowIndex === -1) return;

        // Specific cell
        const TP = relevantColumn[relevantRowIndex];
        //
        const FP = splitData[relevantRowIndex].reduce((a, b) => a + b) - TP;
        // (All predictions) - (specific cell)
        const FN = relevantColumn.reduce((a, b) => a + b) - TP;
        // (All true anything else) - (false positives)
        const TN = totalSamples - relevantColumn.reduce((a, b) => a + b) - FP;

        categorizedData[label] = {
            TP: TP,
            TN: TN,
            FP: FP,
            FN: FN,
            SENS: (100 * TP) / (TP + FN),
            SPEC: (100 * TN) / (TN + FP),
            ACC: (100 * (TP + TN)) / (TP + FP + TN + FN),
            MCC: (TP * TN - FP * FN) / Math.sqrt((TP + FP) * (TP + FN) * (TN + FP) * (TN + FN)),
        };
    });

    const averageMCC =
        Object.values(categorizedData)
            .map((x) => x.MCC)
            .reduce((a, b) => a + b) / 4;
    const accuracyLabels =
        (100 *
            Object.values(categorizedData)
                .map((x) => x.TP)
                .reduce((a, b) => a + b)) /
        totalSamples;

    return { averageMCC, accuracyLabels, sampleInfo: categorizedData };
}

// console.log(findMetrics(testData));
