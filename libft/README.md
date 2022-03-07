# Libft
## Part1

### memset
* 메모리를 채운다. b에 c를 len만큼 채운다.
* size_t --> 부호 없는 정수형. 32비트 운영체제에선 부호 없는 32비트 정수, 64비트 운영체제에선 부호 없는 64비트 정수.
```c
void  *(void *b, int c, size_t len)
```

### bzero
* memset이랑 비슷한데 이건 따로 채울 데이터를 정해 주는 게 아니라 무조건 0으로 채운다.
* memset을 만들었으니, memset에 채울 데이터 c를 0으로 해서 전달해주면 된다.
```c
void  (void *s, size_t n)
```

### memcpy
* 말 그대로 메모리 카피함수.
```c
void  *(void *dst, const void *src, size_t n)
```

### memccpy
* n개 복사하는데 도중에 c만나면 c다음 주소 리턴.(복사 쉽게 하기 위해서)
* 못 만나면 리턴 널
```c
void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
```

### memmove
* dst < src면 dst 처음부터 복사. overlapped 방지 위해.
* dst > src면 그냥 뒤에서부터 복사. memcpy가 뒤에서부터 복사하게 구현했기 때문에 이 때 memcpy 사용.
```c
void	*memmove(void *dst, const void *src, sieze_t len)
```

### memchr
* 문자열 s에서 unsigned char c를 n범위 안에서 조사.
* c 형변환 필요.
* const void 포인터로는 값을 비교할 수 없다. 변환한 뒤 역참조 하는 식으로 진행해야 한다.
```c
void	*ft_memchr(const void *s, int c, size_t n)
```

### memcmp
* strcmp랑 비슷하다. 대신 이것도 const void가 아니라 const unsigned char로 변환한 뒤 사용해야 한다.
```c
int	ft_memcmp(const void *s1, const void *s2, size_t n)
```

### strlen
* 문자열 길이 구하는 함수
```c
size_t	ft_strlen(const char *s);
```

### strlcpy
* c02-10. 크기 제한 문자열 복사 함수. NULL 종료를 보장해야 한다.
* size - 1 만큼 복사하고 마지막 문자를 널로 채운다.
* strlcpy, strlcat은 생성하려고 한 문자열 전체 길이를 반환한다. strlcpy에서는 src의 길이가 반환된다.
* ft_strlen을 하기 전에 src 널체크를 해줘야 한다. ft_strlen은 s가 널이어도 무조건 접근한다.
```c
size_t	strlcpy(char *dst, const char *src, size_t dstsize)
```

### strlcat
* c03-05
* <https://whatdocumentary.tistory.com/45>
*  strcat 함수와 동일하다. 보안 목적을 위해 strcat 대신 사용한다.
* 복사될 문자열의 길이는 size - dst_len - 1(\0)이다. 끝에 널문자를 삽입한다.
*  반환값은 dst와 복사된 src의 길이의 총합이다. 여기에는 NULL 값은 제외되어 계산된다.
    - 여기서 예외 처리를 size가 dst길이 보다 작으면 그냥 리턴 0 되게 했었는데 그렇게 하면 안 됐었다.
    - <https://m.blog.naver.com/PostView.nhn?blogId=01191879872&logNo=221111654384&proxyReferer=https:%2F%2Fwww.google.com%2F>
    - 여기서 보면 strlen(src)는 고정이고, dest가 size보다 작으면 srclen + size, dest가 size보다 크면 srclen + dstlen이 되어야 한다.
* size가 아무리 커도 src_len만큼 복사되고 끝난다.

* j < src_len 은 src범위를 벗어나는 곳을 접근하는 것을 방지해준다. (dest_len + j) + 1 < size 는 dest_len을 제외한 size - 1만큼만 복사가 될 수
 있도록 한다. 마지막 널문자를 추가해주기 위함이다.
* 이전 코드에서 strlen을 사용해서 구현했을 때 war machine에서 bus error 났었음. 원인이 뭘까?
```c
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (dst[i] && i < dstsize)
		i++;
	while (src[j] && (i + j + 1) < dstsize)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i < dstsize)
		dst[i + j] = '\0';
	return (i + ft_strlen(src));
}
```

### strchr
* 문자열 s에서 char형 c가 "처음" 나타나는 위치 반환.
* 문자열 끝을 나타내는 널문자까지 포함하여 검색해야 한다. 
```c
char	*ft_strchr(const char *s, int c);
```

### strrchr
* 문자열 s에서 char형 c가 "마지막으로" 나타나는 위치 반환.
* 문자열 끝을 나타내는 널문자까지 포함하여 검색해야 한다.
* size_t는 unsigned int!! while (i >= 0) 이렇게 하면 안 되고 while (i > 0) 이렇게 사용하기.
```c
char	*ft_strrchr(const char *s, int c);
```

### strnstr
* 문자열 haystack에서 문자열 needle이 "처음" 나타나는 위치 반환.
* 대신 n길이 내에서 검색.
* 이 때 haystack 앞에서부터 n 길이만큼의 범위 사이에서만 검색한다는 거.
```c
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
```

### strncmp
* n개만큼 문자열 비교 함수.
```c
int	ft_strncmp(const char *s1, const char *s2, size_t n);
```

### atoi
* C04 - 03문제에서 int형 범위 말고 unsigned long long까지 고려해야 함.
* 문자열을 정수로 바꾸는 함수.
* 문자열 길이가 20넘어가면 양수일 때 -1, 음수일 때 0으로 값이 고정됨.
* 피신에서는 +, -가 여러 번 반복 돼도 됐었는데, 원래 atoi함수에서는 두 개 이상 넘어가면 안 됨. while문을 if문으로 바꾸어 부호 검사하고, 그 다음부턴 while문으로 숫자 검사하면 올바르게 고쳐진다.
```c
int	ft_atoi(const char *str)
```

### isalpha
* 알파벳이면 1 아니면 0
```c
int	ft_isalpha(int c)
```

### isdigit
* 숫자면 1 아니면 0
```c
int	ft_isdigit(int c)
```

### isalnum
* 알파벳 또는 숫자면 1 아니면 0
```c
int	ft_isalnum(int c)
```

### isascii
* 아스키범위 내 값이면 1 아니면 0
```c
int	ft_isascii(int c)
```

### isprint
* printable이면 1 아니면 0
* 0~31, 127
```c
int	ft_isprint(int c)
```

### toupper
* 소문자를 대문자로
```c
int	ft_toupper(int c)
```

### tolower
* 대문자를 소문자로
```c
int	ft_tolower(int c)
```

### calloc
* malloc과 같은데, 대신 할당된 공간을 0으로 채워줌.
* 앞에서 구현했던 bzero를 사용하여 메모리를 0으로 채워주면 된다.
* size에 자료형 크기가 들어가는 거고, count에 size 크기 자료형 몇 개만큼의 공간 할당할 건지 적어주면 된다. 최종적으로 count * size크기만큼의 공간이 할당 되는 것이다.
```c
void	*ft_calloc(size_t count, size_t size);
```

### strdup
* 공간을 malloc으로 할당해주고, 해당 공간에 복사하고 주소 리턴해주는 함수.
* C07 - 00문제
* strdup
  - strdup() 함수는 문자 s 를 복사하고 복사된 문자열을 가리키는 포인터를 반환한다. 문자를 복사할 공간을 확보하기 위해서 내부적으로 malloc(3)이 호출된다.
  - 복사된 문자열의 주소를 가리키는 포인터를 반환한다. 에러발생시에는 NULL 을 되돌려준다.

* malloc
  - memory allocation
  - 동적할당이라는 것은 프로그램 실행중에 동적으로 메모리를 할당하는 것을 말한다.
  - 함수 원형은 void* malloc(size_t size) 로, 동적할당 후 해당 데이터 타입으로 형변환을 해줘야 한다. 또한 메모리 크기는 자료형마다 다르기 때문에 sizeof()을 사용하여 자료형의 크기에 원하는 할당 크기를 곱해준다.

```c
char	*ft_strdup(const char *src);
```

## PART2
### ft_substr
* s에서 start부터 len까지 substring 만들어서 반환.
* s가 빈 문자열이거나, start위치가 s의 길이를 넘어가는 경우 예외처리.
* 마지막에 널문자 붙여서 반환해준다.
```c
char	*ft_substr(char const *s, unsigned int start, size_t len)
```

### ft_strjoin
* s1에 s2를 붙인다.
* s1이나 s2가 널이면 예외처리 한다.
```c
char	*ft_strjoin(char const *s1, char const *s2)
```

### ft_strtrim
* s1의 앞뒤로 set안에 있는 문자열을 자른다.
* 앞에서부터 set안에 있는 문자열이 안 나올 때까지 자르고, 뒤에서부터 또 set안에 있는 문자열이 안 나올 때까지 자르는 것이다.
* 앞 뒤가 잘린 substring이 반환되는 것이다.
```c
char	*ft_strtrim(char const *s1, char const *set)
```

### ft_split
* 문자열을 특정 문자 기준으로 잘라서 이중포인터로 저장하여 반환해준다.
* ㅠㅠ..피신 때 했던 걸로 수정해서 냈는데 워머신에서 버스에러가 난다... --> ft_calloc으로 해결
* strs에 str만큼 할당 할 때, str이 제대로 할당 안 돼서 그냥 리턴 널해버리면 그 전에 strs에 할당해뒀던 메모리를 해제하지 못한 상황에서
 그냥 널이 리턴되니까 그 전에 있던 strs를 해제해 줄 수 있게 바꿔야 한다.
* 아ㅏ...여기선 malloc 말고 ft_calloc 활용하기. 애초에 0으로 채워놓으면 나중에 마지막에 따로 0 채워서 리턴 안 해줘도 된다...
```c
char	**ft_split(char const *s, char c);
```

### ft_iota
* 이것도 ft_calloc활용.
* 10진수 정수니까 10씩 나눠서 길이 얼마나 나오는지 확인하는데, 음수나 0이면 1부터 시작해서 세야 한다. 음수는 -붙여주기 위해서, 0은 while문에 걸려서 바로 빠져나가 버리니까.
```c
char	*ft_itoa(int n)
```

### ft_strmapi
* 각 문자에 함수 f를 적용시켜 새로운 문자열을 반환시켜 주는 함수.
* i는 인덱스이다.
```c
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
```

### ft_putchar_fd
* fd 파일에 문자 쓰는 함수.
* 파일 제대로 안 열리면(fd가 < 0 이면) 그냥 리턴. (예외처리)
```c
void	ft_putchar_fd(char c, int fd);
```

### ft_putstr_fd
* 이건 fd 파일에 문자열 쓰는 함수.
* write자체가, buffer에 있는 데이터를 buffer size만큼 fd에 쓰는 거기 때문에 그냥 
```c
void	ft_putstr_fd(char *s, int fd)
{
	if (!s || fd < 0)
		return ;
	write(fd, s, ft_strlen(s));
}
```
이렇게 해주면 된다.

### ft_putend_fd
* 그냥 putstr하고 마지막에 개행 넣어주는 것만 차이점 있음.
```c
void	ft_putendl_fd(char *s, int fd)
```

### ft_putnbr_fd
* 숫자 fd에 문자로 써주는 함수.
* 음수일 때는 '-' 먼저 붙여주고 양수로 바꿔서 재귀 돌려줄 거기 때문에, -끝값만 오버플로 처리 위해 그냥 써준다.
* -끝값 아닌 경우, 한자리 수가 될 때까지 나눠서 계속 재귀로 보내고, 한 자리 수가 남으면 그대로 출력하고
* 그 다음부터는 재귀 탈출하면서 % 10한 값을 출력하게 한다.
```c
void	ft_putnbr_fd(int n, int fd)
```

## BONUS PART
### ft_lstnew
* 리스트 생성 함수.
* 동적 할당 제대로 된 경우, content 채우고, next 널로 채워서 해당 리스트 포인터 반환.
```c
t_list	*ft_lstnew(void *content)
```

### ft_lstadd_front
* 리스트 맨 앞에 노드 삽입하는 함수.
* 리스트 시작점이 바뀌는 것이기 때문에, 이중포인터로 전달해주고 시작포인터도 갱신해줘야 한다.
```c
void	ft_lstadd_front(t_list **lst, t_list *new)
```

### ft_lstsize
* 리스트의 크기 알아내는 함수.
* 리스트가 널일 때까지 while문 돌면서 size값 갱신
```c
int	ft_lstsize(t_list *lst)
```

### ft_lstlast
* 리스트 마지막 노드 알아내는 함수.
* 리스트의 next가 널일 때까지 while문 돌다가 마지막위치 반환.
```c
t_list	*ft_lstlast(t_list *lst)
```

### ft_lstadd_back
* 리스트 마지막에 노드 삽입하는 함수.
* 함수인자가 널인 경우 예외처리
* lst가 널이면 그냥 바로 new 대입해주고, 아니라면 ft_lstlast로 마지막 노드 알아내서 next에 new 연결해주면 된다.
```c
void	ft_lstadd_back(t_list **lst, t_list *new)
```

### ft_lstdelone
* 노드 삭제하는 함수.
* t_list구조체에서 content가 void 포인터였어서, 그냥 바로 노드를 free시키면 안 되고 content를 del함수로 적절하게 처리해주고 난 다음에 노드 free 시켜줘야 한다.
```c
void	ft_lstdelone(t_list *lst, void (*del)(void *))
```

### ft_lstiter
* 리스트 돌면서 각 content에 f함수 적용시키는 함수.
```c
void    ft_lstiter(t_list *lst, void (*f)(void *))
```

### ft_lstmap
* 각 lst노드에 함수 적용시킨 새로운 new list 반환 하는 함수.
* 중간에 새로운 노드 생성에 문제가 생겼을 시, 이전에 만들었던 노드들을 모두 삭제해주고 리턴 돼야 하기 때문에 ft_lstclear를 써준다.
```c
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
```
