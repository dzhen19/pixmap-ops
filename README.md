# pixmap-ops

Image manipulation demos based on the PPM image format.

![greenscreen](https://user-images.githubusercontent.com/55254786/218018300-8d115564-802e-441d-8b71-12457c2cdf93.png)

## How to build

*Windows*

Open git bash to the directory containing this repository.

```
pixmap-ops $ mkdir build
pixmap-ops $ cd build
pixmap-ops/build $ cmake -G "Visual Studio 17 2022" ..
pixmap-ops/build $ start pixmap-ops.sln
```

Your solution file should contain two projects: `pixmap_art` and `pixmap_test`.
To run from the git bash command shell, 

```
pixmap-ops/build $ ../bin/Debug/pixmap_test
pixmap-ops/build $ ../bin/Debug/pixmap_art
```

*macOS*

Open terminal to the directory containing this repository.

```
pixmap-ops $ mkdir build
pixmap-ops $ cd build
pixmap-ops/build $ cmake ..
pixmap-ops/build $ make
```

To run each program from build, you would type

```
pixmap-ops/build $ ../bin/pixmap_test
pixmap-ops/build $ ../bin/pixmap_art
```

## Image operators / Results

### Gaussian Blur: 
![Radio - Page 1 (12)](https://user-images.githubusercontent.com/55254786/218019265-ace473c6-1e5a-4708-a6b6-25cd69a3624d.png)


### Green Screen: 
![Radio - Page 1 (11)](https://user-images.githubusercontent.com/55254786/218018859-3ab7483d-92c2-45fd-9d9c-0521f73f6c1d.png)


### Original Images: 
![Radio - Page 1 (10)](https://user-images.githubusercontent.com/55254786/218017197-6c32ab09-67c9-495f-9c00-87a6e24cf36f.png)

### Horizontal flip
`earth.flipHorizontal().save("flipped_horizontal.png");`

![flipped_horizontal](https://user-images.githubusercontent.com/55254786/218016569-20b167c7-e764-4e5c-86f1-8f0ab6af5d13.png)

### Vertical flip
`earth.flipVertical().save("flipped_vertical.png");`

![flipped_vertical](https://user-images.githubusercontent.com/55254786/218017255-b9ea8cd1-72e6-42eb-8b7d-deb97cd06262.png)

### Rotate 90 degrees
`earth.rotate90().save("rotate_90.png");`

![rotate_90](https://user-images.githubusercontent.com/55254786/218017280-5580f1c4-a8ad-4750-9080-1010d9670043.png)

### Swirl
`earth.swirl().save("swirl.png");`

![swirl](https://user-images.githubusercontent.com/55254786/218017333-6be4579c-f4e7-4abd-8c15-44dcf7298575.png)

### Add
`earth.add(shrek).save("earth_add.png");`

![earth_add](https://user-images.githubusercontent.com/55254786/218017362-b4499265-e5a5-4191-8dfb-3288279477c8.png)

### Subtract
`earth.subtract(shrek).save("earth_subtract.png");`

![earth_subtract](https://user-images.githubusercontent.com/55254786/218017381-78ad97e3-cabe-4635-8707-576796ec37e4.png)

### Multiply
`earth.multiply(shrek).save("earth_multiply.png");`

![earth_multiply](https://user-images.githubusercontent.com/55254786/218017401-7ef864b0-277b-4df1-b93b-79c056f96fc8.png)

### Difference
`earth.difference(shrek).save("earth_diff.png");`

![earth_diff](https://user-images.githubusercontent.com/55254786/218017430-a9ac37ea-4c1d-436f-92fa-ed2d8903c6c6.png)

### Lightest 
`earth.lightest(shrek).save("earth_lightest.png");`

![earth_lightest](https://user-images.githubusercontent.com/55254786/218017664-fc1fee40-e214-4d35-918e-9b2c789805c8.png)

### Darkest
`earth.lightest(shrek).save("earth_darkest.png");`

![earth_darkest](https://user-images.githubusercontent.com/55254786/218017683-5811f87b-febf-4800-8d63-5ea354e7b924.png)




