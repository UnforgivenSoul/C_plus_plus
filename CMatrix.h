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
		try
		{
			constexpr bool is_arithmetic_t = std::is_arithmetic<T>::value;
			if (!is_arithmetic_t)
				throw 1;
		}
		catch (int err)
		{
			exit(err);
		}
	}

	CMatrix(int _row_c, int _col_c)
	{
		try
		{
			constexpr bool is_arithmetic_t = std::is_arithmetic<T>::value;
			if (!is_arithmetic_t)
				throw 1;
		}
		catch (int err)
		{
			exit(err);
		}

		row_count = _row_c;
		col_count = _col_c;
		std::vector<std::vector<T>> matrix(row_count, std::vector<T>(col_count));
		CurrentMatrix = matrix;
		matrix.clear();
	}

	CMatrix(const CMatrix & CopyMatrix) = default;

	CMatrix(CMatrix && MovableMatrix) = default;

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

	// Функция создания матрицы производит вызов функций установки размеров и ввода матрицы
	void CreateNewMatrix(std::istream& InputStream, std::ostream& OutputStream, int row_c, int col_c)
	{
		SetMatrixSize(row_c, col_c);
		CurrentMatrix = InputNewMatrix(InputStream, OutputStream);
	}

	bool OutputMatrix(std::ostream& stream) const
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

	int GetRowCount() const
	{
		return row_count;
	}

	int GetColCount() const
	{
		return col_count;
	}

	void DeleteMatrix()
	{
		CurrentMatrix.clear();
		col_count = 0;
		row_count = 0;
	}

	auto GetMax() const
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

	auto GetMin() const
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

	// Подсчет суммы строки
	auto GetRowSum(int row_number) const
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

	// Подсчет суммы столбца
	auto GetColSum(int col_number) const
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


	T GetCellValue(int row, int col) const
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

	bool MultiplyMatrices(CMatrix SecondMatrix)
	{
		int FirstRowCount = row_count;
		int FirstColCount = col_count;
		int SecondRowCount = SecondMatrix.GetRowCount();
		int SecondColCount = SecondMatrix.GetColCount();
		T iteration_result = 0;

		CMatrix<T> MultiplicationResult(FirstRowCount, SecondColCount);

		if (FirstColCount == SecondRowCount)
		{
			for (int i = 0; i < FirstRowCount; i++)
				for (int j = 0; j < SecondColCount; j++)
				{

					for (int k = 0; k < FirstColCount; k++)
					{
						iteration_result = CurrentMatrix[i][k] * SecondMatrix.GetCellValue(k, j);
						MultiplicationResult.AddToCellValue(i, j, iteration_result);
					}
				}
			MultiplicationResult.OutputMatrix(std::cout);
			return true;
		}

		else
		{
			return false;
		}
	}
}; 
