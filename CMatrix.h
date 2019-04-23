#pragma once
template<class T>

class CMatrix
{
private:

	int col_count;
	int row_count;
	std::vector<std::vector<T>> CurrentMatrix;

public:

	CMatrix()
	{

	}

	CMatrix(int _row_c, int _col_c)
	{
		row_count = _row_c;
		col_count = _col_c;
		std::vector<std::vector<T>> matrix(row_count, std::vector<T>(col_count));
		CurrentMatrix = matrix;
		matrix.clear();
	}

	CMatrix(const CMatrix & CopyMatrix) = default;

	CMatrix(CMatrix && MovableMatrix) = default;

public:

	void SetMatrixSize(int row_c, int col_c)
	{
		row_count = row_c;
		col_count = col_c;
	}

	auto InputNewMatrix(std::istream& InputStream, std::ostream& OutputStream)
	{
		std::vector<std::vector<T>> matrix(row_count, std::vector<T>(col_count));
		for (int i = 0; i < row_count; i++)
			for (int j = 0; j < col_count; j++)
			{
				OutputStream << "Введите элемент " << i + 1 << " строки " << j + 1 << " столбца." << std::endl;
				InputStream >> matrix[i][j];

				while (InputStream.fail())
				{
					OutputStream << "Введите элемент " << i + 1 << " строки " << j + 1 << " столбца." << std::endl;
					InputStream.clear();
					while (InputStream.peek() != '\n') 
						InputStream.get();
					InputStream >> matrix[i][j];
				}
			}
		return matrix;
	}

	void CreateNewMatrix(std::istream& InputStream, std::ostream& OutputStream, int row_c, int col_c)
	{
		SetMatrixSize(row_c, col_c);
		CurrentMatrix = InputNewMatrix(InputStream, OutputStream);
	}

	bool OutputMatrix(std::ostream& stream)
	{
		if (!CurrentMatrix.empty())
		{
			for (int i = 0; i < row_count; i++)
			{
				for (int j = 0; j < col_count; j++)
				{
					stream << CurrentMatrix[i][j] << " ";
				}
				stream << "\n";
			}
			return true;
		}
		else
		{
			return false;
		}
	}

	int GetRowCount()
	{
		return row_count;
	}

	int GetColCount()
	{
		return col_count;
	}

	void DeleteMatrix()
	{
		CurrentMatrix.clear();
	}

	auto GetMax()
	{
		std::vector<T> max_vector;
		T max;
		if (!CurrentMatrix.empty())
		{
			for (int i = 0; i < row_count; i++)
			{
				for (int j = 0; j < col_count; j++)
					max_vector.push_back(CurrentMatrix[i][j]);
			}
			max = *std::max_element(max_vector.begin(), max_vector.end());
			return std::make_pair(true, max);
		}
		else
		{
			return std::make_pair(false, max);
		}
	}

	auto GetMin()
	{
		std::vector<T> min_vector;
		T min;
		if (!CurrentMatrix.empty())
		{
			for (int i = 0; i < row_count; i++)
			{
				for (int j = 0; j < col_count; j++)
					min_vector.push_back(CurrentMatrix[i][j]);
			}
			min = *std::min_element(min_vector.begin(), min_vector.end());
			return std::make_pair(true, min);
		}
		else
		{
			return std::make_pair(false, min);
		}
	}

	auto GetRowSum(int row_number)
	{
		T sum_of_row;
		std::vector<T> summation_row;

		if (!CurrentMatrix.empty() and row_number <= row_count)
		{
			for (int j = 0; j < col_count; j++)
				summation_row.push_back(CurrentMatrix[row_number - 1][j]);

			sum_of_row = std::accumulate(summation_row.begin(), summation_row.end(), T(0));
			return std::make_pair(true, sum_of_row);
		}
		else
		{
			return std::make_pair(false, sum_of_row);
		}
	}

	auto GetColSum(int col_number)
	{
		T sum_of_col;
		std::vector<T> summation_col;

		if (!CurrentMatrix.empty() and col_number <= col_count)
		{
			for (int i = 0; i < row_count; i++)
				summation_col.push_back(CurrentMatrix[i][col_number - 1]);

			sum_of_col = std::accumulate(summation_col.begin(), summation_col.end(), T(0));
			return std::make_pair(true, sum_of_col);
		}
		else
		{
			return std::make_pair(false, sum_of_col);
		}
	}

	bool TransponeMatrix()
	{
		std::vector<std::vector<T>> transposed_matrix(col_count, std::vector<T>(row_count));

		if (!CurrentMatrix.empty())
		{
			if (row_count == col_count)
			{
				for (int i = 0; i < row_count; i++)
				{
					for (int j = 0; ((j < col_count) & (j < i)); j++)
						std::swap(CurrentMatrix[i][j], CurrentMatrix[j][i]);
				}
			}
			else
			{
				for (int i = 0; i < row_count; i++)
					for (int j = 0; j < col_count; j++)
					{
						transposed_matrix[j][i] = CurrentMatrix[i][j];
					}

				CurrentMatrix = transposed_matrix;
				std::swap(col_count, row_count);
				transposed_matrix.clear();
			}
			return true;
		}
		else
		{
			return false;
		}
	}


	T GetCellValue(int row, int col)
	{
		return CurrentMatrix[row][col];
	}

	void SetCellValue(int row, int col, T value)
	{
		CurrentMatrix[row][col] = value;
	}

	void AddToCellValue(int row, int col, T value)
	{
		CurrentMatrix[row][col] += value;
	}

	bool MultiplyByNumber(T multiplier)
	{
		if (!CurrentMatrix.empty())
		{
			for (int i = 0; i < row_count; i++)
				for (int j = 0; j < col_count; j++)
					CurrentMatrix[i][j] *= multiplier;

			return true;
		}

		else
		{
			return false;
		}
	}

	void FillInMatrixRandomly(int lower_bound, int upper_bound, int row_c, int col_c)
	{
		std::random_device rd;
		std::default_random_engine rng(rd());

		SetMatrixSize(row_c, col_c);
		std::vector<std::vector<T>> matrix(row_count, std::vector<T>(col_count, 0));
		CurrentMatrix = matrix;
		std::uniform_int_distribution<> dist(lower_bound, upper_bound);

		for (int i = 0; i < row_count; i++)
			for (int j = 0; j < col_count; j++)
				CurrentMatrix[i][j] = dist(rng);
	}
};
