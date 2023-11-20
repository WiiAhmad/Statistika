#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

struct UngroupedData
{
    float classValue;
    int frequency;
};

struct GroupedData
{
    float startClass;
    float endClass;
    int frequencySum = 0;
    float midPoint = (startClass + endClass) / 2;
};

void ProcessUngroupedData(UngroupedData data[], int n)
{
    cout << "ungrouped data" << endl;
    float totalFrequency = 0;
    float totalScore = 0;

    for (int i = 0; i < n; i++)
    {
        totalFrequency += data[i].frequency;
        totalScore += data[i].classValue * data[i].frequency;
    }

    // definisi median dan modus dalam data
    float median, modus;
    float mean = totalScore / totalFrequency;
    // menghitung nilai tengah

    sort(data, data + n, [](const UngroupedData &a, const UngroupedData &b)
         { return a.classValue < b.classValue; });

    if (n % 2 == 0)
    {
        int classmedian = (n + 1) / 2;
        median = data[classmedian].classValue;
    }
    else
    {
        int classmedian = n / 2;
        median = (data[classmedian].classValue + data[classmedian + 1].classValue) / 2;
    }

    // calculate mode
    int maxFrequency = 0;
    for (int i = 0; i < n; i++)
    {
        if (data[i].frequency > maxFrequency)
        {
            maxFrequency = data[i].frequency;
            modus = data[i].classValue;
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (data[i].classValue != 0 || data[i].frequency != 0)
        {
            cout << "Score : " << data[i].classValue;
            cout << " Frequency : " << data[i].frequency << endl;
        }
    }
    cout << endl;

    float smallestData = data[0].classValue;
    float largestData = data[n - 1].classValue;
    float range = largestData - smallestData;
    double logTotalFrequency = log10(totalFrequency);
    int k2 = 1 + (3.3 * logTotalFrequency);
    int k = k2 + 1;
    int interval = (range / k) + 1;

    // Menampilkan
    cout << "ukuran pemusat data" << endl;
    cout << "Range: " << range << endl;
    cout << "Log Total Frequency : " << logTotalFrequency << endl;
    cout << "Kelas : " << k << endl;
    cout << "Interval : " << interval << endl;
    cout << "Total Frequency : " << totalFrequency << endl;
    cout << "Total Score : " << totalScore << endl;
    cout << "Mean : " << (float)totalScore / totalFrequency << endl;
    cout << "Median : " << median << endl;
    cout << "Modus : " << modus << endl;
    cout << "Mean : " << mean << endl;

    // simpangan rata rata dan baku pada data tunggal
    float xbar = (float)totalScore / totalFrequency;

    cout << "xbar : " << xbar << endl;

    // simpangan rata rata
    // average absolute deviation
    float averageAbsoluteDeviation = 0;
    for (int i = 0; i < n; i++)
    {
        averageAbsoluteDeviation += abs(data[i].classValue - xbar) * data[i].frequency;
    }
    averageAbsoluteDeviation = averageAbsoluteDeviation / totalFrequency;
    cout << "Simpangan Rata Rata : " << averageAbsoluteDeviation << endl;

    // simpangan baku
    // standard deviation
    float standardDeviation = 0;
    for (int i = 0; i < n; i++)
    {
        standardDeviation += pow(data[i].classValue - xbar, 2) * data[i].frequency;
    }
    standardDeviation = sqrt(standardDeviation / totalFrequency);
    cout << "Simpangan Baku : " << standardDeviation << endl;
}

// fungsi untuk mengubah data ungrouped menjadi grouped
void groupedData(UngroupedData data[], GroupedData data2[], int n)
{
    // mengurutkan data dari yang terkecil
    sort(data, data + n, [](const UngroupedData &a, const UngroupedData &b)
         { return a.classValue < b.classValue; });

    // menghitung jumlah frekuensi
    int totalFrequency = 0;
    for (int i = 0; i < n; i++)
    {
        totalFrequency += data[i].frequency;
    }

    // menghitung jumlah kelas
    double logTotalFrequency = log10(totalFrequency);
    int k2 = 1 + (3.3 * logTotalFrequency);
    int k = k2 + 1;

    // menghitung interval
    float smallestData = data[0].classValue;
    float largestData = data[n - 1].classValue;
    float range = largestData - smallestData;
    int interval = (range / k) + 1;

    int index;
    float startClass = smallestData;
    float b = interval * k;
    float endRange = smallestData + b;

    for (index = 0; index < k; index++)
    {
        // cout << "index = " << index << endl;
        int index2 = 1;
        for (float j = startClass; j < endRange; j++)
        {
            // cout << "j = " << j << endl;
            if (index2 == 1)
            {
                data2[index].startClass = j;
                // cout << "start class = " << data2[index].startClass << endl;
            }
            if (index2 == interval)
            {
                data2[index].endClass = j;
                // cout << "end class = " << data2[index].endClass << endl;
                startClass = j + 1;
                // cout << "start class = " << startClass << endl;
            }
            // cout << "index2 = " << index2 << endl;
            index2++;
            // cout << "index2 = " << index2 << endl;
        }
    }

    for (int index = 0; index < k; index++)
    {
        // cout << "index = " << index << endl;
        for (int i = data2[index].startClass; i <= data2[index].endClass; i++)
        {
            cout << "i = " << i << endl;
            for (int j = 0; j < n; j++)
            {
                // cout << "data[j].classValue = " << data[j].classValue << endl;
                if (data[j].classValue == i)
                {
                    data2[index].frequencySum += data[j].frequency;
                    // cout << "frequency sum = " << data2[index].frequencySum << endl;
                }
            }
        }
    }

    // menampilkan data
    cout << "Grouped Data" << endl;
    cout << "Total Frequency : " << totalFrequency << endl;
    cout << "Kelas : " << k << endl;
    cout << "Interval : " << interval << endl;
    cout << "Range : " << range << endl;
    cout << "Smallest Data : " << smallestData << endl;
    cout << "Largest Data : " << largestData << endl;

    // menghitung nilai tengah
    for (int i = 0; i < k; i++)
    {
        data2[i].midPoint = static_cast<float>(data2[i].startClass + data2[i].endClass) / 2;
    }

    cout << "start class\tend class\tfrequency sum\tmid point\n";

    // menampilkan kelas grouped data , frekuensi tiap kelas, dan nilai tengah
    for (int j = 0; j < index; j++)
    {
        cout << data2[j].startClass << "\t\t" << data2[j].endClass << "\t\t" << data2[j].frequencySum << "\t\t" << data2[j].midPoint << endl;
    }
    // frekuensi relatif dan persentase
    float relativeFrequency;
    float percentage;
    for (int i = 0; i < k; i++)
    {
        relativeFrequency = (float)data2[i].frequencySum / totalFrequency;
        percentage = relativeFrequency * 100;
        cout << "Relative Frequency : " << relativeFrequency;
        cout << "\tPercentage : " << percentage << endl;
    }

    // frekuensi kumulatif
    int cumulativeFrequency = 0;
    for (int i = 0; i < k; i++)
    {
        cumulativeFrequency += data2[i].frequencySum;
        cout << "Cumulative Frequency : " << cumulativeFrequency << endl;
    }
    // frekuensi kumulatif relatif
    float cumulativeRelativeFrequency = 0;
    for (int i = 0; i < k; i++)
    {
        cumulativeRelativeFrequency += (float)data2[i].frequencySum / totalFrequency;
        cout << "Cumulative Relative Frequency : " << cumulativeRelativeFrequency << endl;
    }
    // frekuensi kumulatif persentase
    float cumulativePercentage = 0;
    for (int i = 0; i < k; i++)
    {
        cumulativePercentage += (float)data2[i].frequencySum / totalFrequency * 100;
        cout << "Cumulative Percentage : " << cumulativePercentage << endl;
    }
    // menentukan kelas mean
    float meanClass;
    for (int i = 0; i < k; i++)
    {
        meanClass += data2[i].midPoint * data2[i].frequencySum;
    }
    meanClass = meanClass / totalFrequency;
    cout << "Mean Class : " << meanClass << endl;
    // menentukan kelas modus
    int maxFrequency = 0;
    float modusClass;
    for (int i = 0; i < k; i++)
    {
        if (data2[i].frequencySum > maxFrequency)
        {
            maxFrequency = data2[i].frequencySum;
            modusClass = data2[i].midPoint;
        }
    }
    cout << "Modus Class : " << modusClass << endl;
    // menentukan kelas median
    float medianClass;
    int totalFrequency2 = 0;
    for (int i = 0; i < k; i++)
    {
        totalFrequency2 += data2[i].frequencySum;
    }
    cout << "Total Frequency : " << totalFrequency2 << endl;
    if (totalFrequency2 % 2 == 0)
    {
        int classmedian = (totalFrequency2 + 1) / 2;
        for (int i = 0; i < k; i++)
        {
            if (classmedian <= data2[i].frequencySum)
            {
                medianClass = data2[i].midPoint;
                break;
            }
            else
            {
                classmedian -= data2[i].frequencySum;
            }
        }
    }
    else
    {
        int classmedian = totalFrequency2 / 2;
        for (int i = 0; i < k; i++)
        {
            if (classmedian <= data2[i].frequencySum)
            {
                medianClass = data2[i].midPoint;
                break;
            }
            else
            {
                classmedian -= data2[i].frequencySum;
            }
        }
    }
    cout << "Median Class : " << medianClass << endl;
    // menentukan simpangan rata-rata
    float xbar = meanClass;
    cout << "xbar : " << xbar << endl;
    // simpangan rata-rata
    float averageAbsoluteDeviation = 0;
    for (int i = 0; i < k; i++)
    {
        averageAbsoluteDeviation += abs(data2[i].midPoint - xbar) * data2[i].frequencySum;
    }
    averageAbsoluteDeviation = averageAbsoluteDeviation / totalFrequency;
    cout << "Simpangan Rata Rata : " << averageAbsoluteDeviation << endl;
    // simpangan baku
    float standardDeviation = 0;
    for (int i = 0; i < k; i++)
    {
        standardDeviation += pow(data2[i].midPoint - xbar, 2) * data2[i].frequencySum;
    }
    standardDeviation = sqrt(standardDeviation / totalFrequency);
    cout << "Simpangan Baku : " << standardDeviation << endl;
    // variansi
    float variance = 0;
    for (int i = 0; i < k; i++)
    {
        variance += pow(data2[i].midPoint - xbar, 2) * data2[i].frequencySum;
    }
    variance = variance / totalFrequency;

    cout << "Variance : " << variance << endl;
    // kuartil 1
    float q1;
    int totalFrequency3 = 0;
    for (int i = 0; i < k; i++)
    {
        totalFrequency3 += data2[i].frequencySum;
    }
    cout << "Total Frequency : " << totalFrequency3 << endl;
    int classq1 = (totalFrequency3 + 1) / 4;
    for (int i = 0; i < k; i++)
    {
        if (classq1 <= data2[i].frequencySum)
        {
            q1 = data2[i].midPoint;
            break;
        }
        else
        {
            classq1 -= data2[i].frequencySum;
        }
    }
    cout << "Q1 : " << q1 << endl;
    // kuartil 2
    float q2;
    int totalFrequency4 = 0;
    for (int i = 0; i < k; i++)
    {
        totalFrequency4 += data2[i].frequencySum;
    }
    cout << "Total Frequency : " << totalFrequency4 << endl;
    int classq2 = (totalFrequency4 + 1) / 2;
    for (int i = 0; i < k; i++)
    {
        if (classq2 <= data2[i].frequencySum)
        {
            q2 = data2[i].midPoint;
            break;
        }
        else
        {
            classq2 -= data2[i].frequencySum;
        }
    }
    cout << "Q2 : " << q2 << endl;
    // kuartil 3
    float q3;
    int totalFrequency5 = 0;
    for (int i = 0; i < k; i++)
    {
        totalFrequency5 += data2[i].frequencySum;
    }
    cout << "Total Frequency : " << totalFrequency5 << endl;
    int classq3 = (totalFrequency5 + 1) * 3 / 4;
    for (int i = 0; i < k; i++)
    {
        if (classq3 <= data2[i].frequencySum)
        {
            q3 = data2[i].midPoint;
            break;
        }
        else
        {
            classq3 -= data2[i].frequencySum;
        }
    }
    cout << "Q3 : " << q3 << endl;
}

int main()
{
    UngroupedData data[100];
    GroupedData data2[100];

    cout << "pilih data yang akan dimasukan : \n";
    cout << "1. Ungrouped Data Raw          example : 1 2 3 4 5\n";
    cout << "2. Ungrouped Data with Freq to Grouped    example : 1 2 3 4 5\n";
    cout << "3. Ungrouped Data              example class 12 frequency 2\n";
    cout << "4. Grouped Data                this have start class, end class and frequencySum\n";

    int choice, n = 0;
    float score;

    cout << "your choice : ";
    cin >> choice;

    switch (choice)
    {

    case 1:
        // need input with direct scores and frequencies, not raw data
        do
        {
            cout << "Enter the score : ";
            cin >> score;
            if (score == 000)
            {
                break;
            }
            else
            {
                bool found = false;

                for (int i = 0; i < n; i++)
                {
                    if (data[i].classValue == score)
                    {
                        data[i].frequency++;
                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    data[n].classValue = score;
                    data[n].frequency = 1;
                    n++;
                }
            }
        } while (score != 000);

        ProcessUngroupedData(data, n);
        break;
    case 2:
        // need input with direct scores and frequencies, not raw data
        do
        {
            cout << "Enter the score : ";
            cin >> score;
            if (score == 000)
            {
                break;
            }
            else
            {
                bool found = false;

                for (int i = 0; i < n; i++)
                {
                    if (data[i].classValue == score)
                    {
                        data[i].frequency++;
                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    data[n].classValue = score;
                    data[n].frequency = 1;
                    n++;
                }
            }
        } while (score != 000);

        groupedData(data, data2, n);
        break;
    case 3:
        do
        {
            cout << "Enter the score : ";
            cin >> score;
            if (score == 000)
            {
                break;
            }
            else
            {
                data[n].classValue = score;
                cout << "Enter the frequency : ";
                cin >> data[n].frequency;
                n++;
            }
        } while (score != 000);

        groupedData(data, data2, n);

        break;

    case 4:
        do
        {
            cout << "Enter the start class : ";
            cin >> score;
            if (score == 000)
            {
                break;
            }
            else
            {
                data2[n].startClass = score;
                cout << "Enter the end class : ";
                cin >> data2[n].endClass;
                cout << "Enter the frequency : ";
                cin >> data2[n].frequencySum;
                n++;
            }
        } while (score != 000);
        break;

    case 0:
        cout << "exiting...\n";
        break;

    default:
        cout << "wrong input\n";
    }
}