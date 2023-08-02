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
            "odomtopicsub = my_py_pkg.odomtopicsub:main",
            "cmdvelpublisher = my_py_pkg.cmdvelpublisher:main",
            "elevator_service = my_py_pkg.elevator_service:main",
            "customtopic = my_py_pkg.custom_topic_publisher:main"
           
        ],
    },
)
