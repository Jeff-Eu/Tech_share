# Graphics in Android

## Matrix
* [It's `Row major`](https://stackoverflow.com/questions/32190006/android-matrix-setvalues-row-major-or-column-major)

* Rotation unit is `degree` instead of `radian`. E.g.,
	```
	Matrix.postRotate(float degrees, float px, float py)
	```

* Matrix's elements are ordered by rows, from left to right.
E.g., the function below from mvb. Notice the order of the `f` array.
	```java
		// https://math.stackexchange.com/questions/13150/extracting-rotation-scale-values-from-2d-transformation-matrix/13165
		// https://math.stackexchange.com/questions/237369/given-this-transformation-matrix-how-do-i-decompose-it-into-translation-rotati
		/* todo: Here sx, sy are both larger than 0.
		* In the future we need to take negative values of sx, sy into consideration.
		*/
		public static float[] getScaleVector(Matrix matrix) {
			float sx, sy;
			float[] f = new float[9];
			matrix.getValues(f);
			sx = (float) Math.hypot(f[0], f[1]);
			sy = (float) Math.hypot(f[3], f[4]);

			// https://stackoverflow.com/questions/3160347/java-how-initialize-an-array-in-java-in-one-line
			return new float[]{sx, sy};
		}
	```


