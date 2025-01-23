// ����������� ������ �������� ��� ������ Array
template<typename T>
class Array<T>::ConstIterator {
private:
  const T* current_;  // ������� �������
  const T* end_;      // ����� ��������� ��������

public:
  // ����������� ���������
  ConstIterator(const T* start, const T* end) : current_(start), end_(end) {}

  // ��������� �������� �������� (������ ��� ������)
  const T& get() const {
    return *current_;
  }

  // ������� � ���������� ��������
  void next() {
    if (hasNext()) {
      ++current_;
    }
  }

  // ��������, ���� �� ��������� �������
  bool hasNext() const {
    return current_ < end_;
  }
};
