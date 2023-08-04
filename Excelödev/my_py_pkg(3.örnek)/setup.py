from setuptools import setup

package_name = 'my_py_pkg'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='huseyin',
    maintainer_email='huseyin@todo.todo',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
           "shapedrawer = my_py_pkg.shapedrawernode:main",
           "pathfollower = my_py_pkg.pathfollowernode:main",
           "turtlecontrol = my_py_pkg.turtlecontroler.py:main"
           
        ],
    },
)
