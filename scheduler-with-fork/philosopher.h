#define N 5

void philosopher(int i)
{
  while (TRUE) {
    think();
    take_fork(i);
    take_fork((i+1) % N);
    eat();
    put_fork(i);
    put_fork((i+1) % N);
  }
}

void take_forks(int i)
{
  down(&mutex);
  state[i] = HUNGRY;
  test(i);
  up(&mutex);
  down(&s[i]);
}

void put_forks(int i)
{
  down(&mutex);
  state[i] = THINKING;
  test(LEFT);
  test(RIGHT);
  up(&mutex);
}

void test(i)
{
  if(state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING){
      state[i] = EATING;
      up(&s[i]);
  }
}
