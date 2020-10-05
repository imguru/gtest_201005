
# 라이브러리
1. 정적 라이브러리(libgtest.a)
  - 라이브러리가 실행 파일에 포함된다.
  - 바이너리의 크기가 크다.
  - 라이브러리가 변경되면, 반드시 다시 컴파일 해야 한다.
  - 라이브러리가 실행 파일에 포함되어 있기 때문에, 바이너리만 있으면 구동 가능하다.

2. 동적 라이브러리(libgtest.so)
  - 라이브러리가 실행 파일에 포함되지 않는다.
  - 실행 시간에 사용하는 라이브러리를 로드한다. 
  - 바이너리의 크기에 영향을 미치지 않는다.
  - 라이브러리가 변경되어도, 다시 컴파일 할 필요가 없다.
  - 라이브러리가 실행 파일에 포함되지 않기 때문에, 바이너리와 별도의 라이브러리 파일이 같이 있어야 한다.

구글 테스트는 정적 라이브러리를 권장합니다.
정적 라이브러리를 통해 사용하는 것이 테스트 프레임워크의 신뢰성에 더 좋다.

# 정적 라이브러리 작성 방법
```
$ googletest/googletest/scripts/fuse_gtest_files.py ~/chansik.yun

$ g++ gtest/gtest-all.cc -c -I.
$ g++ gtest/googletest/googletest/gtest_main.cc -c -I.
$ ar rcv libgtest.a gtest-all.o gtest_main.o

```
